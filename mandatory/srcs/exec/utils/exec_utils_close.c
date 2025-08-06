/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:11:00 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/06 16:01:46 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_fd_in_array(t_content *content)
{
	size_t	i;

	i = 0;
	while (content->fd_array[i] != -8 && i < content->hdoc_length)
		i++;
	content->fd_array[i] = content->h_fd;
}

void	ft_close_open(t_content *content, char *temp_file)
{
	int		old_fd;
	size_t	i;

	i = 0;
	old_fd = content->h_fd;
	close(content->h_fd);
	content->h_fd = open(temp_file, O_RDONLY | O_CREAT, 0644);
	while (content->fd_array[i] != old_fd)
		i++;
	content->fd_array[i] = content->h_fd;
}

void	ft_close_in_out_saved(t_content *content)
{
	if (content->stdin_saved != -2)
	{
		close(content->stdin_saved);
		content->stdin_saved = -2;
	}
	if (content->stdout_saved != -2)
	{
		close(content->stdout_saved);
		content->stdout_saved = -2;
	}
}

void	ft_close_std(t_content *content)
{
	if (content->stdin_saved != -2 && content->stdin_saved != -1)
	{
		close(content->stdin_saved);
		content->stdin_saved = -2;
	}
	if (content->stdout_saved != -2 && content->stdout_saved != -1)
	{
		close(content->stdout_saved);
		content->stdout_saved = -2;
	}
}

void	ft_close_all(t_content *content)
{
	ft_close_pipes(content->array_ptr);
	if ((content && content->infile != -2) && (content->infile != -1))
	{
		close(content->infile);
		content->infile = -2;
	}
	if ((content && content->outfile != -2) && (content->outfile != -1))
	{
		close(content->outfile);
		content->outfile = -2;
	}
	if (content->h_fd != -2 && content->h_fd != -1)
	{
		close(content->h_fd);
		content->h_fd = -2;
	}
}
