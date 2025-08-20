/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:36:56 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/20 15:42:49 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_prompt(t_array *array)
{
	char	*error_converted;
	char	*joined_prompt;

	error_converted = ft_itoa(array->p_exit_status); // PROTECTED
	if (!error_converted)
	{
		array->p_exit_status = 1;
		joined_prompt = ft_strdup("\001\033[1;36m\002maxishell \001\033[0m\002");
		// PROTECTED
	}
	else
	{
		joined_prompt = ft_strjoin(error_converted, // PROTECTED
									"\001\033[1;36m\002 | maxishell \001\033[0m\002");
		free(error_converted);
	}
	if (!joined_prompt)
	{
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		array->p_exit_status = 1;
		return (NULL);
	}
	return (joined_prompt);
}

int	get_true_line(char **line)
{
	char	*temp;
	size_t	i;
	int		returned_value;

	i = 0;
	returned_value = 0;
	while ((*line)[i] && ft_isspace((*line)[i]) == 1)
		i++;
	if (i == ft_strlen(*line))
	{
		ft_wipe(line);
		return (0);
	}
	temp = ft_strdup(&(*line)[i]); // PROTECTED
	if (!temp)
		returned_value = 1;
	free(*line);
	*line = ft_strdup(temp); // PROTECTED
	if (!*line)
		returned_value = 1;
	free(temp);
	if (returned_value == 1)
		ft_putendl_fd("maxishell: malloc error", 2);
	return (returned_value);
}

void	*manage_readline(char **line, t_array *array, t_list **var)
{
	char	*prompt;

	prompt = NULL; //ft_join_prompt(array);
	if (prompt)
		*line = readline(prompt);
	else
		*line = readline("maxishell>");
	if (g_signal == SIGINT)
		array->p_exit_status = 128 + SIGINT;
	g_signal = 0;
	free(prompt);
	if (*line == NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_free_env(*var);
		exit(array->p_exit_status);
	}
	if (line && *line && **line != '\0')
		add_history(*line);
	if (get_true_line(line) == 1)
		array->p_exit_status = 1;
	return (NULL);
}

int	call_check_syntax(char *line, char *temp_line, t_array *array)
{
	if (check_syntax(temp_line))
	{
		if (line[0] != '\0')
			array->p_exit_status = 2;
		free(line);
		free(temp_line);
		return (1);
	}
	return (0);
}

int	launch_shell(t_list **var, t_array *array)
{
	char	*line;
	char	***cmd_splitted;

	cmd_splitted = NULL;
	signal(SIGINT, deal_with_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		manage_readline(&line, array, var);
		array->size = 0;
		array->content = NULL;
		if (!line)
			continue ;
		if (line[0] != '\0')
			if (line[0] != '\0')
				process_command(line, var, array, &cmd_splitted);
	}
	return (0);
}
