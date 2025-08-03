/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:25:47 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/03 12:52:47 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	h_expansion(char *line, t_content *content, char *temp_file)
{
	char	*expanded_line;

	expanded_line = expand_word(line, content->env, content->array_ptr);
	if (!expanded_line)
	{
		free(temp_file);
		return (ft_open_error(content, "expanded_line"));
	}
	ft_putendl_fd(expanded_line, content->h_fd);
	free(expanded_line);
	return (0);
}

int	get_hdoc_fd(t_content *content)
{
	size_t	i;
	int		fd;

	i = 0;
	while (i < content->hdoc_length && content->fd_array[i] == -42)
		i++;
	fd = content->fd_array[i];
	content->fd_array[i] = -42;
	return (fd);
}

int	ft_use_hdoc(t_content *content, size_t i)
{
	if (content->files[i].type == HDOC)
	{
		content->infile = get_hdoc_fd(content);
		if (dup2(content->infile, STDIN_FILENO) == -1)
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
