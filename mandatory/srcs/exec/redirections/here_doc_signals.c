/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:12:15 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/05 17:40:12 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	controld_hdoc_dealing(char *line, t_content *content, int *data,
		char *temp_file)
{
	char	*temp;

	(void)temp_file;
	if (!line)
	{
		temp = ft_itoa(data[2]);
		if (temp)
		{
			ft_putstr_fd("maxishell: warning: here-document at line ",
				STDERR_FILENO);
			ft_putstr_fd(temp, STDERR_FILENO);
			free(temp);
			ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
			ft_putstr_fd(content->cmd_splitted[data[0]][data[1]],
				STDERR_FILENO);
			ft_putstr_fd("')\n", STDERR_FILENO);
		}
		if (!temp)
			ft_open_error(content, NULL);
		return (1);
	}
	return (0);
}

int	get_stdin(t_content *content)
{
	if (dup2(content->stdin_saved, STDIN_FILENO) == -1)
	{
		if (content->stdin_saved)
			close(content->stdin_saved);
		content->stdin_saved = -2;
		ft_dup2_pb(content, "content->stdin_saved");
		return (1);
	}
	return (0);
}

int	sigint_hdoc_dealing(t_content *content, char *temp_file, char *line)
{
	if (g_signal == SIGINT)
	{
		// if (!*content->env)
		// 	ft_putstr_fd("\n", STDERR_FILENO);
		unlink(temp_file);
		free(temp_file);
		if (get_stdin(content) == 1)
			return (1);
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
