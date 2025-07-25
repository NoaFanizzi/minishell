/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:25:47 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/25 11:10:26 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_hdoc_fd(int *array)
{
	size_t	i;
	int		fd;

	i = 0;
	while (i < FD_SETSIZE && array[i] == -42)
		i++;
	if (i == FD_SETSIZE)
	{
		// TODO jsp quoi faire
		ft_putstr_fd("maxishell: too much fd opened\n", STDERR_FILENO);
		return (-100);
	}
	fd = array[i];
	array[i] = -42;
	return (fd);
}

int	ft_use_hdoc(t_content *content, size_t i)
{
	int	position;

	position = 0;
	if (content->files[i].type == HDOC)
	{
		position = content->pos;
		if (content->pos % 2 != 0)
			position += 1;
		content->infile = get_hdoc_fd(content->fd_array);
		if (dup2(content->infile, STDIN_FILENO) == -1) // PROTECTED
			return (ft_dup2_pb(content, "temp_file"));
		close(content->infile);
		content->infile = -2;
	}
	return (0);
}

int	loop_hdoc(t_array *array, size_t size, size_t i)
{
	size_t	j;
	int		returned_value;

	j = 0;
	while (j < size)
	{
		if (array->content[i].files[j].type == HDOC)
		{
			signal(SIGINT, deal_with_sigint_hdoc);
			returned_value = ft_deal_with_hdoc(&array->content[i], &j);
			signal(SIGINT, deal_with_sigint);
		}
		if (returned_value == O_ERROR || returned_value == 1)
			return (1);
		j++;
	}
	return (0);
}

int	ft_process_here_doc(t_array *array)
{
	int		i;
	size_t	size;

	i = 0;
	while (i < array->size)
	{
		if (array->content[i].hdoc)
		{
			size = array->content[i].files[0].size;
			if (loop_hdoc(array, size, i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
