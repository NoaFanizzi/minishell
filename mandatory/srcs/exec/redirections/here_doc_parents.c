/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_parents.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:03:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/26 13:26:01 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	controld_hdoc_dealing(char *line, t_content *content, int *data,
		char *temp_file)
{
	char	*temp;

	if (!line)
	{
		temp = ft_itoa(data[2]); // PROTECTED
		if (!temp)
		{
			close(content->stdin_saved);
			unlink(temp_file);
			free(temp_file);
			free(line);
			ft_open_error(content, NULL);
			ft_exit(content);
		}
		ft_putstr_fd("maxishell: warning: here-document at line ",
			STDERR_FILENO);
		ft_putstr_fd(temp, STDERR_FILENO);
		free(temp);
		ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(content->cmd_splitted[data[0]][data[1]], STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	sigint_hdoc_dealing(t_content *content, char *temp_file, char *line)
{
	if (g_signal == SIGINT)
	{
		unlink(temp_file);
		free(temp_file);
		if (dup2(content->stdin_saved, STDIN_FILENO) == -1) // PROTECTED
			return (ft_dup2_pb(content, "content->stdin_saved"));
		free(line);
		close(content->h_fd);
		content->h_fd = -1;
		if (content->h_fd != -1)
			close(content->h_fd);
		close(content->stdin_saved);
		content->stdin_saved = -2;
		content->array_ptr->p_exit_status = 130;
		g_signal = 0;
		content->h_fd = -2;
		return (1);
	}
	return (0);
}

int	ft_launch_here_doc(t_content *content, int *data, char *temp_file)
{
	char	*line;

	data[2] = 0;
	while (1)
	{
		line = readline("> ");
		data[2] += 1;
		if (sigint_hdoc_dealing(content, temp_file, line) == 1)
			return (1);
		if (controld_hdoc_dealing(line, content, data, temp_file) == 1)
			break ;
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
		if (ft_get_temp_file(&temp_file, content) == O_ERROR) // PROTECTED
			return (1);
		content->h_fd = open(temp_file, O_RDWR | O_CREAT, 0644); // PROTECTED
		if (content->h_fd == -1)
		{
			content->h_fd = -2;
			return (free(temp_file), ft_open_error(content, "content->h_fd"));
		}
		add_new_fd_in_array(content);
		*i += 1;
		content->array_ptr->hdoc_length += *i;
		if (ft_launch_here_doc(content, data, temp_file) == 1)
			return (1);
	}
	ft_close_open(content, temp_file);
	unlink(temp_file);
	return (free(temp_file), 0);
}

int	ft_deal_with_hdoc(t_content *content, size_t *i)
{
	char	*temp_file;
	int		returned_value;

	temp_file = NULL;
	returned_value = 0;
	content->stdin_saved = dup(STDIN_FILENO);
	if (content->stdin_saved == -1)
		return (ft_dup2_pb(&content->array_ptr->content[0], "stdin"));
	while (*i < content->files->size && content->files[*i].type == HDOC)
	{
		returned_value = prepare_hdoc(content, i, temp_file);
		if (returned_value == 1 || returned_value == O_ERROR)
			return (returned_value);
	}
	close(content->stdin_saved);
	content->stdin_saved = -2;
	return (0);
}
