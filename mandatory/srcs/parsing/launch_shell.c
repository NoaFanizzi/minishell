/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:36:56 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/30 01:11:32 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_prompt(t_array *array)
{
	char	*error_converted;
	char	*joind_prompt;

	error_converted = ft_itoa(array->p_exit_status);
	if (!error_converted)
		joind_prompt = ft_strdup("\001\033[1;36m\002maxishell \001\033[0m\002");
	else
	{
		joind_prompt = ft_strjoin(error_converted,
				"\001\033[1;36m\002 | maxishell \001\033[0m\002");
		free(error_converted);
	}
	if (!joind_prompt)
	{
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		array->p_exit_status = 1;
		return (NULL);
	}
	return (joind_prompt);
}

void	check_tty(char **line, char *prompt)
{
	if (isatty(STDIN_FILENO))
		*line = readline(prompt);
	else
		*line = readline(NULL);
}

void	*manage_readline(char **line, t_array *array, t_list **var)
{
	char	*prompt;

	prompt = ft_join_prompt(array);
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
		array->p_exit_status = 0;
		ft_free_env(*var);
		exit(array->p_exit_status);
	}
	if (line && *line && **line != '\0')
		add_history(*line);
	return (NULL);
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

	array->p_exit_status = 0;
	cmd_splitted = NULL;
	signal(SIGINT, deal_with_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		manage_readline(&line, array, var);
		array->size = 0;
		array->content = NULL;
		if (line[0] != '\0')
		if (line[0] != '\0')
			process_command(line, var, array, &cmd_splitted);
	}
	return (0);
}

void	print_cmd_splitted(char ***cmd_splitted)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (cmd_splitted[k])
	{
		i = 0;
		printf("cmd n%d\n", k);
		while (cmd_splitted[k][i])
		{
			printf("word n%d : [%s]\n", i, cmd_splitted[k][i]);
			i++;
		}
		printf("word n%d : [%s]\n\n", i, cmd_splitted[k][i]);
		k++;
	}
	printf("////////////////\n\n");
}

// void	print_cmd(char **cmd)
// {
// 	int	k;

// 	k = 0;
// 	while (cmd[k])
// 	{
// 		printf("word n%d : [%s]\n\n", k, cmd[k]);
// 		k++;
// 	}
// 	printf("////////////////\n\n");
// }