/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:34:46 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/29 18:34:06 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_pid(t_array *array)
{
	pid_t	pid;
	int		status;
	int		sig;

	status = 0;
	sig = 0;
	(void)array;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == array->content[array->size - 1].pid)
		{
			if (WIFEXITED(status))
				array->p_exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig != SIGPIPE)
					array->p_exit_status = 128 + WTERMSIG(status);
			}
		}
		pid = waitpid(-1, &status, 0);
	}
}

int	count_hdoc(t_content *content)
{
	size_t	i;
	size_t	count;
	size_t	length;

	i = 0;
	count = 0;
	length = 0;
	if (content->files)
		length = content->files->size;
	while (i < length)
	{
		if (content->files[i].type == HDOC)
			count++;
		i++;
	}
	return (count);
}

int	ft_load_hdoc_fd(t_content *content)
{
	size_t	i;

	i = 0;
	content->hdoc_length = count_hdoc(content);
	content->fd_array = ft_calloc(sizeof((content->hdoc_length) + 1),
			sizeof(int)); // PROTECTED
	if (!content->fd_array)
	{
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		content->array_ptr->p_exit_status = 1;
		return (0);
	}
	while (i < content->hdoc_length)
	{
		content->fd_array[i] = -8;
		i++;
	}
	return (1);
}

int	ft_load_preliminary_infos(t_list **env, t_array *array)
{
	size_t	i;

	i = 0;
	array->pipe = NULL;
	array->content[i].hdoc_length = 0;
	while ((int)i < array->size)
	{
		array->content[i].array_ptr = array;
		array->content[i].expar = NULL;
		array->content[i].env = env;
		array->content[i].pos = i;
		array->content[i].size = array->size;
		array->content[i].error_code = -500;
		array->content[i].h_fd = -2;
		array->content[i].infile = -2;
		array->content[i].outfile = -2;
		array->content[i].stdin_saved = -2;
		array->content[i].stdout_saved = -2;
		if (ft_load_hdoc_fd(&array->content[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_init_exec(t_list **env, t_array *array)
{
	int	redir_value;

	redir_value = 0;
	if (array->size == 0)
		return ;
	if (!ft_load_preliminary_infos(env, array))
		return ;
	if (array->size == 1)
	{
		redir_value = ft_get_redir_dad(array, env);
		if (redir_value == 0 || redir_value == 2 || redir_value == -10)
		{
			if (array->content[0].stdin_saved != -2)
				close(array->content[0].stdin_saved);
			if (array->content[0].stdout_saved != -2)
				close(array->content[0].stdout_saved);
			return ;
		}
	}
	if (ft_init_pipe(array) == 1)
		return ;
	if (ft_process_here_doc(array) == 1)
		return (ft_close_pipes(array));
	child_management(env, array);
	deal_with_signal_after_exec();
}
