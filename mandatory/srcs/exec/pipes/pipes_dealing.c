/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_initialisation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:51:56 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/01 16:52:26 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_pipe(t_array *array)
{
	int	i;

	i = 0;

	array->pipe = malloc(sizeof(*array->pipe) * (array->size - 1));
	while(i < array->size - 1)
	{
		if (pipe(array->pipe[i]) == -1)
		{
			perror("pipe");
			ft_exit(&array->content[0]);
		}
		i++;
	}
}

void	ft_close_pipes(t_array *array)
{
	int	i;

	i = 0;
	while(i < array->size - 1)
	{
		if(array->pipe)
		{
			close(array->pipe[i][0]);
			close(array->pipe[i][1]);
		}
		i++;
	}
	free(array->pipe);
	array->pipe = NULL;
}