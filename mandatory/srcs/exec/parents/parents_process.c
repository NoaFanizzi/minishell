/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:34:46 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/05 12:19:16 by nofanizz         ###   ########.fr       */
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
		
		if(WIFEXITED(status))
			array->p_exit_status = WEXITSTATUS(status);
		if(WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if(sig != SIGPIPE)
				array->p_exit_status = 128 + WTERMSIG(status);
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

int	ft_process_here_doc(t_array *array)
{
	int	i;
	size_t	j;
	size_t	size;
	int returned_value;

	i = 0;
	j = 0;
	while(i < array->size)
	{
		if(array->content->hdoc)
		{
			size = array->content[i].files[0].size;
			j = 0;
			while(j < size)
			{
				if(array->content[i].files[j].type == HDOC)
				{
					returned_value = ft_deal_with_hdoc(&array->content[i], &j);
					break;
				}
				returned_value = ft_deal_with_hdoc(&array->content[i], &j);
				if(returned_value == O_ERROR)
				{
					dprintf(STDERR_FILENO, "value returned = %d\n", returned_value);
					return(1);
				}
				j++;
			}
		}
		i++;
	}
	return(0);
}

void	ft_init_exec(t_list **env, t_array *array)
{
	int	i;
	int redir_value;

	i = 0;
	redir_value = 0;
	g_array = array;
	//ft_display_array_content(array);
	if(array->size == 0)
		return;
	ft_load_preliminary_infos(env, array);
	if(array->size == 1)
	{
		redir_value = ft_get_redir_dad(array, env);
		if(redir_value == 0 || redir_value == 2)
			return;
	}
	ft_init_pipe(array);
	ft_process_here_doc(array);
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

