/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 00:46:02 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"                                                                                                                                                                                            

int		count_hdoc(char **command)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (command[i])
    {
        if (ft_strncmp(command[i], "<<", 2) == 0)
        {
            count++;
            i++;
        }
        i++;
    }
	return (count);
}

void	fill_hdocs(char **command, t_heredocs *hdoc, size_t hdoc_count)
{
	size_t i = 0, j = 0;

	while (command[i])
	{
		if (ft_strncmp(command[i], "<<", 2) == 0)
		{
			if (command[i + 1][0] == S_QUOTE || command[i + 1][0] == D_QUOTE)
				hdoc[j].s_quoted = 1;
			else
				hdoc[j].s_quoted = 0;
			hdoc[j].text = NULL;
			hdoc[j].size = hdoc_count;
			j++;
		}
		i++;
	}
}

int	create_hdoc_struct(char **command, t_content *content)
{
	size_t hdoc_count = count_hdoc(command);

	if (hdoc_count == 0)
		return (content->hdoc = NULL, 0);
	content->hdoc = malloc(hdoc_count * sizeof(t_heredocs));
	if (!content->hdoc)
		return (-1);
	fill_hdocs(command, content->hdoc, hdoc_count);
	return (0);
}


char	*ft_join_prompt(t_array *array)
{
	char *error_converted;
	char *joined_prompt;

	error_converted = ft_itoa(array->p_exit_status);
	joined_prompt = ft_strjoin(error_converted, " | maxishell$ ");
	free(error_converted);
	return(joined_prompt);
}

void	get_array_size(char ***cmd_splitted, t_array *array)
{
	size_t	i;

	i = 0;
	while(cmd_splitted[i])
	{
		if (cmd_splitted[i][0] && ft_strncmp(cmd_splitted[i][0], "|", 1) != 0)
			 array->size++;
		i++;
	}
}

void	analyse_command(char ***cmd_splitted, t_array *array)
{
	size_t	cmd_index;
	size_t	struct_index;

	cmd_index = 0;
	struct_index = 0;
	get_array_size(cmd_splitted, array);
	array->content = malloc((array->size) * sizeof(t_content));
	//check malloc
	while(cmd_splitted[cmd_index])
	{
		if (cmd_splitted[cmd_index][0] && strncmp(cmd_splitted[cmd_index][0], "|", 1) != 0)
		{
			if (create_hdoc_struct(cmd_splitted[cmd_index], &array->content[struct_index]) == -1)
				return ;//need to see how to check that
			create_cmd_struct(cmd_splitted, &array->content[struct_index], cmd_index);		
			struct_index++;
		}
		cmd_index++;
	}
	fill_struct_size(array, struct_index);
	return ;
}

void    fill_struct_size(t_array *array, size_t struct_index)
{
	size_t i;
	
    i = 0;
    while (i < struct_index)
		array->content[i++].size = struct_index;

}

void check_tty(char **line, char *prompt)
{
	if (isatty(STDIN_FILENO))
        *line = readline(prompt);
    else
        *line = readline(NULL);
}

void	*manage_readline(char **line, t_array *array)
{
	char *prompt;
	
	prompt = ft_join_prompt(array);
	//check_tty(line, prompt);
	*line = readline(prompt);
	if(g_signal == SIGINT)
		array->p_exit_status = 128 + SIGINT;
	g_signal = 0;
	free(prompt);
	if (*line == NULL)
		return(NULL);
	if (line && *line)
		add_history(*line);
	return(NULL);
}

static int	process_command(char *line, t_list **var, t_array *array, char ***cmd_splitted)
{
	char *temp_line = ft_strdup(line);

	if (check_syntax(temp_line))
	{
		if (line[0] != '\0')
			array->p_exit_status = 2;
		free(line);
		free_command(*cmd_splitted);
		return (1);
	}
	*cmd_splitted = parse_command(&temp_line, var, array);
	if (!*cmd_splitted)
		return (1);
	analyse_command(*cmd_splitted, array);
	ft_init_exec(var, array);
	free(line);
	free_command(*cmd_splitted);
	ft_free_array_content(array);
	return (0);
}

int	launch_shell(t_list **var)
{
	char	*line;
	char	***cmd_splitted;
	t_array	array;

	array.p_exit_status = 0;
	signal(SIGINT, deal_with_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		manage_readline(&line, &array);
		array.size = 0;
		array.content = NULL;
		if (process_command(line, var, &array, &cmd_splitted))
			return (1);
	}
	return (0);
}

//MALLOC AND FT