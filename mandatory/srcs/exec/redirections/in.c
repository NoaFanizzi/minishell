/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:03:11 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/06 16:41:06 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_in(t_content *content, size_t i, size_t position)
{
	content->infile = open(content->cmd_splitted[position][content->files[i]
			.index + 1], O_RDONLY, 0644);
	if (content->infile == -1)
		return (ft_open_error(content,
				content->cmd_splitted[position][content->files[i].index + 1]));
	if (dup2(content->infile, STDIN_FILENO) == -1)
		return (ft_dup2_pb(content,
				content->cmd_splitted[position][content->files[i].index + 1]));
	close(content->infile);
	content->infile = -2;
	return (0);
}

int	ft_deal_with_in(t_content *content, size_t i)
{
	int	position;

	position = 0;
	if (content->files[i].type == IN)
	{
		dprintf(2, "IN FOUND\n");
		position = content->pos;
		if (content->pos != 0)
			position += position;
		if (!(content->cmd_splitted[position][content->files[i].index + 1]))
		{
			ft_putstr_fd("maxishell: syntax error near ", STDERR_FILENO);
			ft_putstr_fd("unexpected token `newline'\n", STDERR_FILENO);
			content->error_code = 2;
			return (O_ERROR);
		}
		if (check_in(content, i, position) == O_ERROR)
		{
			//dprintf(2, "Problem detected in check_in function\n");
			return (O_ERROR);
		}
	}
	return (0);
}
