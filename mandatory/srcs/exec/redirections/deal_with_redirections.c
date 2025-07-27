/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:33:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/27 16:48:28 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_apnd(t_content *content, size_t i, size_t position)
{
	content->outfile = open(content->cmd_splitted[position][content->files[i]
			.index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644); // PROTECTED
	if (content->outfile == -1)
		return (ft_open_error(content,
				content->cmd_splitted[position][content->files[i].index + 1]));
	if (dup2(content->outfile, STDOUT_FILENO) == -1) // PROTECTED
		return (ft_dup2_pb(content,
				content->cmd_splitted[position][content->files[i].index + 1]));
	close(content->outfile);
	content->outfile = -2;
	return (0);
}

int	ft_deal_with_apnd(t_content *content, size_t i)
{
	size_t	position;

	position = 0;
	if (content->files[i].type == APND)
	{
		position = content->pos;
		if (content->pos != 0)
			position += position;
		if (!(content->cmd_splitted[position][content->files[i].index + 1]))
		{
			ft_putstr_fd("maxishell: syntax error near", STDERR_FILENO);
			ft_putstr_fd("unexpected token `newline'\n", STDERR_FILENO);
			content->error_code = 2;
			return (O_ERROR);
		}
		if (check_apnd(content, i, position) == O_ERROR)
			return (O_ERROR);
	}
	return (0);
}

int	ft_is_printable(char c)
{
	if (c >= 32 && c <= 126)
		return (0);
	return (1);
}

// @$#W%$E^%XR&C^UTYG
