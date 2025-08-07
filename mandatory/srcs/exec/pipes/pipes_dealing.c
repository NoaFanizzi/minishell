/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_dealing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:51:56 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/07 17:33:47 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pipe_array(t_array *array)
{
	if (array->size > 1)
	{
		array->pipe = malloc(sizeof(*array->pipe) * (array->size - 1));
			// PROTECTED
		if (!array->pipe)
		{
			perror("pipe");
			array->p_exit_status = 1;
			return (1);
		}
	}
	return (0);
}

int	ft_init_pipe(t_array *array)
{
	size_t	i;

	i = 0;
	if (array->size * 2 >= FD_SETSIZE)
	{
		ft_putstr_fd("maxishell: cannot make pipe", STDERR_FILENO);
		ft_putendl_fd("for command: Too many open files", STDERR_FILENO);
		array->p_exit_status = 1;
		return (1);
	}
	if (get_pipe_array(array) == 1)
		return (1);
	while (i < array->size - 1)
	{
		if (pipe(array->pipe[i]) == -1) // PROTECTED
		{
			perror("pipe");
			array->p_exit_status = 1;
			ft_close_pipes(array, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_close_pipes(t_array *array, size_t length)
{
	size_t	i;

	i = 0;
	if (!array->pipe)
		return ;
	while (i < array->size - 1 && i != length)
	{
		if (!array->pipe)
			return ;
		if (array->pipe)
		{
			close(array->pipe[i][0]);
			close(array->pipe[i][1]);
		}
		i++;
	}
	free(array->pipe);
	array->pipe = NULL;
}
