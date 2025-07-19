/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/19 15:06:03 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check cases when there is one commnad, or nothing or idk but you understood

//syntax error: unexpected end of input after `|'.     pipe end
//syntax error near unexpected token `|'.       pipe beginning
//syntax error near unexpected token `<'.        wrong redirection
//syntax error: unmatched quote      unclosed quotes


char	***parse_command(char *line, t_list **var, t_array *array)
{	
	char 	**command = NULL;
	char	*str;
	char	***cmd_splitted = NULL;
	int		k;
	int		i;

	k = 0;
	str = ft_strdup(line);
	if (!str)
		return (NULL);
	free(line);
	str = expand_word(str, var, array);
	if (!str)
		return (NULL);
	//printf("str = %s\n\n", str);
	command = quotes_splitting(command, str);
	free(str);
	if (!command)
		return (NULL);//error
	k = 0;
		while (command[k])
	{
		//printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	//printf("\n\n");
	contiguous_quotes(&command);
	if (!command)
		return (NULL);
	k = 0;
	while (command[k])
	{
		//printf("Aword n%d : %s\n", k + 1, command[k]);
		k++;
	}
	//printf("\n\n");
	command = space_splitting(command);
	if (!command)
		return (NULL);//error
	k = 0;
	while (command[k])
	{
		//printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	//printf("\n\n");
	command = meta_splitting(command);
	if (!command)
	return (NULL);//error
	k = 0;
	while (command[k])
	{
		//printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	cmd_splitted = command_splitting(command);
	if (!cmd_splitted)
		return (NULL);
	//printf("\n\n");
	k = 0;
	while (cmd_splitted[k])
	{
		i = 0;
		printf("\ncommand n%d\n", k + 1);
		if (!cmd_splitted[k][i])
		 	printf("NULL\n");
		while (cmd_splitted[k][i])
		{
			printf("word n%d : %s\n", i + 1, cmd_splitted[k][i]);
			i++;
		}
		k++;
	}
	free_words(command);
	return (cmd_splitted);
}


int    create_hdoc_struct(char **command, t_content *content)
{
    size_t		hdoc_count;
    size_t		i;
	size_t		j;
    
    i = 0;
	j = 0;
    hdoc_count = 0;
    while (command[i])
    {
        if (ft_strncmp(command[i], "<<", 2) == 0)
        {
            hdoc_count++;
            i++;
        }
        i++;
    }
	//printf("hdoc count : %zu\n", hdoc_count);
    if (hdoc_count == 0)
	{
		content->hdoc = NULL;
		return (0);
	}
	i = 0;
	content->hdoc = malloc(hdoc_count * sizeof(t_heredocs));
	if (!content->hdoc)
			return(-1);
    while (command[i])
    {
		//printf("current : %s\n", command[i]);
        if (ft_strncmp(command[i], "<<", 2) == 0)
        {
            if (command[i + 1][0] == S_QUOTE || command[i + 1][0] == D_QUOTE)
                content->hdoc[j].s_quoted = 1;
            else
                content->hdoc[j].s_quoted = 0;
            content->hdoc[j].text = NULL;
            content->hdoc[j].size = hdoc_count;
			//printf("squoted : %d\n",  content->hdoc[j].s_quoted);
			//printf("text : %s\n",  content->hdoc[j].text);
			//printf("size : %zu\n\n",  content->hdoc[j].size);
			j++;
        }
        i++;
    }
	return(0);
}

char	*ft_join_prompt(t_array *array)
{
	char *error_converted;
	char *joined_prompt;

	error_converted = ft_itoa(array->p_exit_status);
	joined_prompt = ft_strjoin( error_converted, " | maxishell$ ");
	free(error_converted);
	return(joined_prompt);
	
}

void	analyse_command(char ***cmd_splitted, t_array *array, t_list *var)
{
	size_t	cmd_index;
	size_t	struct_index;

	cmd_index = 0;
	struct_index = 0;
	while(cmd_splitted[cmd_index])
	{
		if (cmd_splitted[cmd_index][0] && strncmp(cmd_splitted[cmd_index][0], "|", 1) != 0)
			 array->size++;
		cmd_index++;
	}
	array->content = malloc(( array->size) * sizeof(t_content));
	//check malloc
	cmd_index = 0;
	(void) var;
	while(cmd_splitted[cmd_index])
	{
		if (cmd_splitted[cmd_index][0] && strncmp(cmd_splitted[cmd_index][0], "|", 1) != 0)
		{
			if (create_hdoc_struct(cmd_splitted[cmd_index], &array->content[struct_index]) == -1)
			return ;//need to see how to check that
			quotes_removal(cmd_splitted[cmd_index]);
			create_cmd_struct(cmd_splitted, &array->content[struct_index], cmd_index);
			//test
			size_t i = 0;
			size_t count = count_redir(cmd_splitted[cmd_index]);
			while (i < count)
			{
				// printf("redir index n%d :\n",  array->content[struct_index].files[i].index + 1);
				// printf("redir%d\n\n", (int) array->content[struct_index].files[i].type + 1);
				i++;
			}
			i = 0;
			count = count_cmd_opt(cmd_splitted[cmd_index]);
			//("count_cmd_opt : %zu\n", count);
			while (i < count)
			{
				// printf("CMD n%lu:%s\n", i + 1,  array->content[struct_index].cmd[i]);
				i++;
			}
			i = 0;
			count = count_arg(cmd_splitted[cmd_index]);
			//printf("count_arg : %zu\n", count);
			while (i < count)
			{
				// printf("ARG n%lu:%s\n", i + 1,  array->content[struct_index].arg[i]);
				i++;
			}
			//test			
			struct_index++;
		}
		cmd_index++;
	}
	//free_command(cmd_splitted);TODOAttention gros problemes en vue
	fill_struct_size(array, struct_index);
	return ;
}

void    fill_struct_size(t_array *array, size_t struct_index)
{
	size_t i;
	
    i = 0;
    while (i < struct_index)
    {
		array->content[i].size = struct_index;
        //(array)->content[i].infile = -3;
        //(array)->content[i].outfile = -3;
        i++;
    }
}

// problem if we have two different commands :  echo >> | cat file
int check_redir(char ***cmd, size_t i, size_t j)
{
	size_t	k;

	k = 0;
	// printf("command i : %s\n", cmd[i][j]);
	// printf("command i + 1 : %s\n", cmd[i][j + 1]);
	while (cmd[i][j][k])
	{
		if (cmd[i][j][k] == '<' || cmd[i][j][k] == '>')
		{
			k++;
			if ((cmd[i][j][k - 1] == '<' && cmd[i][j][k] == '<')
				|| (cmd[i][j][k - 1] == '>' && cmd[i][j][k] == '>'))
				k++;
			// printf("cmd[i][j][k] : %c\n", cmd[i][j][k]);
			// printf("cmd[i][j + 1] : %s\n", cmd[i][j + 1]);
			if (cmd[i][j +  1] == 0)
			{
				if (cmd[i + 1])
					printf("bash: syntax error near unexpected token `|'\n");
				else
					printf("bash: syntax error near unexpected token `newline'\n");
				return (1);
			}
			else if (cmd[i][j][k] == 0
				 && cmd[i][j + 1]
				 && cmd[i][j + 1][0]
				 && (cmd[i][j + 1][0] == '|' || cmd[i][j + 1][0] == '>' || cmd[i][j + 1][0] == '<'))
			{
				if (cmd[i][j + 1][0] == '>' && cmd[i][j + 1][1] && cmd[i][j + 1][1] == '>')
					printf("bash: syntax error near unexpected token `>>'\n");	
				else if (cmd[i][j + 1][0] == '<' && cmd[i][j + 1][1] && cmd[i][j + 1][1] == '<')
					printf("bash: syntax error near unexpected token `<<'\n");
				else
					printf("bash: syntax error near unexpected token `%c'\n", cmd[i][j + 1][0]);	
				return (1);
			}
			else if (cmd[i][j][k] == '|' || cmd[i][j][k] == '>' || cmd[i][j][k] == '<')
			{
				if (cmd[i][j][k] == '>' && cmd[i][j][k + 1] && cmd[i][j][k + 1] == '>')
					printf("bash: syntax error near unexpected token `>>'\n");	
				else if (cmd[i][j][k] == '<' && cmd[i][j][k + 1] && cmd[i][j][k + 1] == '<')
					printf("bash: syntax error near unexpected token `<<'\n");
				else
					printf("bash: syntax error near unexpected token `%c'\n", cmd[i][j][k]);	
				return (1);
			}
		}
		k++;
	}
	return (0);
}

int	check_syntax(char ***cmd_splitted)
{
	size_t	i;
	size_t	j;
	
	i = 0;
	if (!cmd_splitted || !cmd_splitted[0] || !cmd_splitted[0][0])
		return (1);
	if (cmd_splitted[0][0][0] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (cmd_splitted[i])
	{
		j = 0;
		while (cmd_splitted[i][j])
		{
			if (check_redir(cmd_splitted, i, j))//print the message inside the function
			  	return (1);
			j++;
		}
		i++;
	}
	printf("i : %zu\n", i);
	printf("str : %s\n", cmd_splitted[i - 1][0]);
	if (i > 0 && cmd_splitted[i - 1] && cmd_splitted[i - 1][0] &&
		cmd_splitted[i - 1][0][0] == '|' &&
		cmd_splitted[i - 1][0][1] == '\0')
	{
		printf("bash: syntax error: unexpected end of input after `|'\n");
		return (1);
	}
	return (0);
}

void	launch_shell(t_list **var)
{
	char	*line;
	char	***cmd_splitted;
	char *prompt;
	t_array	array;
	
	array.p_exit_status = 0;
	signal(SIGINT, deal_with_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = ft_join_prompt(&array);
		line = readline(prompt);
		free(prompt);
		if (line == NULL)
			break;
		if (line)
			add_history(line);
		array.size = 0;
		array.content = NULL;
		cmd_splitted = parse_command(line, var, &array);
		if (!cmd_splitted)
			return ;
		if (check_syntax(cmd_splitted))
			return ;//need to free maybe
		analyse_command(cmd_splitted, &array, *var);
		ft_init_exec(var, &array);
		free_command(cmd_splitted);
		ft_free_array_content(&array);
	}
}
