/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:07:25 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/21 12:25:26 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_load_expar(t_content *content, t_list **env)
{
	content->error_code = 0;
	content->expar = malloc(sizeof(t_expar));
	content->expar->size = content->array_ptr->size;
	content->expar->path = NULL;
	content->expar->options = ct_get_paths(*env, content);
	if (!content->expar->options)
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		content->error_code = 127;
		ft_exit(content);
	}
	return(0);
}

int	ft_prepare_execution(t_content *content, t_list **env)
{
	int	cmd_value;

	cmd_value = 0;
	if(ft_is_built_in_child(content, env) == 1)
		ft_exit(content);
	cmd_value = ft_is_command(content);

	if (cmd_value == 1 || cmd_value == 2)
	{
		//ft_try_builtin et si c'est pas bon, la faut faut print command not found et faire tout le reste
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		content->error_code = 127;
		//printf("aaaaaaaa\n");
		ft_exit(content);
		exit(127);
	}
	return(0);
}


void	child_handler()
{
	g_signal = 1;
}

void	ft_exec_cmd(t_content *content, t_list **env)
{
	char **env_converted;
	env_converted = NULL;

	signal(SIGINT, child_handler);
	signal(SIGQUIT, SIG_DFL);
	ft_load_expar(content, env);
	if(ft_parse_redirections(content) == O_ERROR)
		ft_exit(content);
	ft_prepare_execution(content, env);
	ft_close_all(content);
	ft_free_tab(content->expar->options);
	env_converted = ft_convert_env(*env);
	content->cmd = ft_cmd_join(content->cmd, content->arg);
	if (execve(content->expar->path, content->cmd, env_converted) == -1)
	{
		perror("execve");
		ft_exit(content);
	}
}

void child_management(t_list **env, t_array *array)
{
	int	i;

	i = 0;
	signal(SIGINT, deal_with_signals_in_exec);
	signal(SIGQUIT, deal_with_signals_in_exec);
	while(i < array->size)
	{
		array->content[i].pid = fork();
		if (array->content[i].pid == -1)
			ft_exit(&array->content[i]);
		if (array->content[i].pid == 0)
			ft_exec_cmd(&array->content[i], env);
		i++;
	}
	ft_close_pipes(array);
	ft_wait_pid(array);
}

