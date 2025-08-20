/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:04:17 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/20 15:53:58 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_out(t_content *content, size_t i, size_t position)
{
	content->outfile = open(content->cmd_splitted[position]
		[content->files[i].index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (content->outfile == -1)
		return (ft_open_error(content,
				content->cmd_splitted[position][content->files[i].index + 1]));
	if (dup2(content->outfile, STDOUT_FILENO) == -1)
		return (ft_dup2_pb(content,
				content->cmd_splitted[position][content->files[i].index + 1]));
	close(content->outfile);
	content->outfile = -2;
	return (0);
}

int	ft_deal_with_out(t_content *content, size_t i)
{
	size_t	position;

	position = 0;
	if (content->files[i].type == OUT)
	{
		position = content->pos;
		if (content->pos != 0)
			position += position;
		if ((content->cmd_splitted[position][content->files[i].index
				+ 1]) == NULL)
		{
			ft_putstr_fd("maxishell: syntax error near'", STDERR_FILENO);
			ft_putstr_fd("unexpected token `newline'\n", STDERR_FILENO);
			content->error_code = 2;
			return (O_ERROR);
		}
		if (check_out(content, i, position) == O_ERROR)
			return (O_ERROR);
	}
	return (0);
}
