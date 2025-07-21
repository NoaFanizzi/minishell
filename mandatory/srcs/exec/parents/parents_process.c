/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:34:46 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/21 18:06:35 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_pid(t_array *array)
{
	pid_t pid;
	int status;
	int sig;

	status = 0;
	sig = 0;
	(void)array;
	pid = waitpid(-1, &status, 0);
	while(pid > 0)
	{
		if(pid == array->content[array->size - 1].pid)
		{
			if(WIFEXITED(status))
				array->p_exit_status = WEXITSTATUS(status);
			if(WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if(sig != SIGPIPE)
					array->p_exit_status = 128 + WTERMSIG(status);
			}
		}
		//printf("array->exit_status = %d\n", array->p_exit_status);
		pid = waitpid(-1, &status, 0);
	}
}

void	ft_load_preliminary_infos(t_list **env, t_array *array)
{
	size_t	i;

	i = 0;
	array->pipe = NULL;
	array->hdoc_length = 0;
	array->is_lost = 0;
	//array->p_exit_status = 0;
	while((int)i < array->size)
	{
		array->content[i].array_ptr = array;
		array->content[i].expar = NULL;
		array->content[i].env = env;
		array->content[i].pos = i;
		array->content[i].size = array->size;
		array->content[i].error_code = -5;
		array->content[i].h_fd = -2;
		array->content[i].infile = -2;
		array->content[i].outfile = -2;
		array->content[i].stdin_saved = -2;
		array->content[i].stdout_saved = -2;
		i++;
	}
}

void	ft_init_exec(t_list **env, t_array *array)
{
	int redir_value;

	redir_value = 0;
	if(array->size == 0)
		return;
	ft_load_preliminary_infos(env, array);
	if(array->size == 1)
	{
		redir_value = ft_get_redir_dad(array, env);
		if(redir_value == 0 || redir_value == 2)
			return;
	}
	if(ft_init_pipe(array) == 1)
	{
		array->p_exit_status = 1;
		return;
	}
	if(ft_process_here_doc(array) == 1)
		return(ft_close_pipes(array));
	child_management(env, array);
	signal(SIGINT, deal_with_sigint);
	signal(SIGQUIT, SIG_IGN);
	deal_with_signal_after_exec();
}

