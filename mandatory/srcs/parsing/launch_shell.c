/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:36:56 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 02:14:02 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_prompt(t_array *array)
{
	char	*error_converted;
	char	*joined_prompt;

	error_converted = ft_itoa(array->p_exit_status);
	joined_prompt = ft_strjoin(error_converted, " | maxishell$ ");
	free(error_converted);
	return (joined_prompt);
}

void	check_tty(char **line, char *prompt)
{
	if (isatty(STDIN_FILENO))
		*line = readline(prompt);
	else
		*line = readline(NULL);
}

void	*manage_readline(char **line, t_array *array)
{
	char	*prompt;

	prompt = ft_join_prompt(array);
	check_tty(line, prompt);
	*line = readline(prompt);
	if (g_signal == SIGINT)
		array->p_exit_status = 128 + SIGINT;
	g_signal = 0;
	free(prompt);
	if (*line == NULL)
		return (NULL);
	if (line && *line)
		add_history(*line);
	return (NULL);
}

int	process_command(char *line, t_list **var, t_array *array,
		char ****cmd_splitted)
{
	char	*temp_line;

	temp_line = ft_strdup(line);
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
