/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_parents.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:03:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/06 20:27:01 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_launch_here_doc(t_content *content, int *data, char *temp_file)
{
	char	*line;
	int returned_value;

	data[2] = 0;
	while (1)
	{
		line = readline("> ");//TODO Proteger ca ?
		data[2] += 1;
		if (sigint_hdoc_dealing(content, temp_file, line) == 1)
			return (1);
		returned_value = controld_hdoc_dealing(line, content, data, temp_file);
		if (returned_value == 1)
		{
			close(content->stdin_saved);
			content->stdin_saved = -2;
			break;
		}
		if(returned_value == 2)
		{
			free(temp_file);
			return(1);
		}
		if (!line || ft_strcmp(line,
				content->cmd_splitted[data[0]][data[1]]) == 0)
			break ;
		if (h_expansion(line, content, temp_file) == O_ERROR)
			return (O_ERROR);
	}
	if (line)
		free(line);
	return (0);
}

int	prepare_hdoc(t_content *content, size_t *i, char *temp_file)
{
	int	data[4];

	data[0] = content->pos;
	if (content->pos != 0)
		data[0] += data[0];
	if (content->files[*i].type == HDOC)
	{
		data[1] = content->files[*i].index + 1;
		if (ft_get_temp_file(&temp_file, content) == O_ERROR)
			return (1);
		content->h_fd = open(temp_file, O_RDWR | O_CREAT, 0644); //PROTECTED
		if (content->h_fd == -1)
		{
			content->h_fd = -2;
			free(temp_file);
			return (ft_open_error(content, "content->h_fd"));
		}
		add_new_fd_in_array(content);
		if (ft_launch_here_doc(content, data, temp_file) == 1)
			return (1);
	}
	if(ft_close_open(content, temp_file) == -1)
		return(1);
	unlink(temp_file);
	free(temp_file);
	return (0);
}

int	begin_hdoc(t_content *content, size_t *i)
{
	int		returned_value;
	char	*temp_file;

	returned_value = 0;
	temp_file = NULL;
	while (*i < content->files->size && content->files[*i].type == HDOC)
	{
		returned_value = prepare_hdoc(content, i, temp_file);
		if (returned_value == 1 || returned_value == O_ERROR)
		{
			if (content->stdin_saved != -2)
				close(content->stdin_saved);
			content->stdin_saved = -2;
		}
		if (content->stdin_saved != -2)
			close(content->stdin_saved);
		content->stdin_saved = -2;
		return (returned_value);
	}
	return (3);
}

int	ft_deal_with_hdoc(t_content *content, size_t *i)
{
	int	returned_value;

	returned_value = 0;
	content->stdin_saved = dup(STDIN_FILENO); //PROTECTED
	if (content->stdin_saved == -1)
	{
		content->stdin_saved = -2;
		return (ft_dup2_pb(&content->array_ptr->content[0], "stdin"));
	}
	returned_value = begin_hdoc(content, i);
	if (returned_value != 3)
		return (returned_value);
	close(content->stdin_saved);
	content->stdin_saved = -2;
	return (0);
}
