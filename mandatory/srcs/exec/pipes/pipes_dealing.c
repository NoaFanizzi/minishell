/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_dealing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:51:56 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/25 10:39:32 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_pipe(t_array *array)
{
	int	i;

	i = 0;
	if (array->size >= FD_SETSIZE)
	{
		ft_putstr_fd("maxishell: cannot make pipe", STDERR_FILENO);
		ft_putstr_fd("for command: Too many open files", STDERR_FILENO);
		array->p_exit_status = 1;
		return (1);
	}
	if (array->size != 1)
		array->pipe = malloc(sizeof(*array->pipe) * (array->size - 1));
	while (i < array->size - 1)
	{
		if (pipe(array->pipe[i]) == -1)
		{
			perror("pipe");
			array->p_exit_status = 1;
			ft_exit(&array->content[0]);
		}
		i++;
	}
	return (0);
}

void	ft_close_pipes(t_array *array)
{
	int	i;

	i = 0;
	if (!array->pipe)
		return ;
	while (i < array->size - 1)
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
