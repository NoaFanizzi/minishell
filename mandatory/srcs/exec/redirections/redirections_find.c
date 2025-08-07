/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_find.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:04:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/07 17:49:50 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirections.h"

int	ft_deal_with_redir_parents(t_content *content)
{
	size_t	size;
	size_t	i;

	i = 0;
	if (content->files != NULL && &content->files[0] != NULL)
	{
		size = content->files[0].size;
		while (i < size)
		{
			if (content->array_ptr->size == 1 && ft_is_built_in(content) == 0)
			{
				if (ft_use_hdoc(content, i) == O_ERROR)
					return (1);
			}
			if (ft_deal_with_out(content, i) == O_ERROR)
				return (1);
			if (ft_deal_with_apnd(content, i) == O_ERROR)
				return (1);
			if (ft_deal_with_in(content, i) == O_ERROR)
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_deal_with_redir_child(t_content *content)
{
	size_t	size;
	size_t	i;

	i = 0;
	if (content->files != NULL && &content->files[0] != NULL)
	{
		size = content->files[0].size;
		while (i < size)
		{
			if (ft_use_hdoc(content, i) == O_ERROR)
				return (1);
			if (ft_deal_with_out(content, i) == O_ERROR)
				return (1);
			if (ft_deal_with_apnd(content, i) == O_ERROR)
				return (1);
			if (ft_deal_with_in(content, i) == O_ERROR)
				return (1);
			i++;
		}
	}
	return (0);
}

void	ft_deal_with_pipes(t_content *content)
{
	if ((content->size > 1 && content->pos > 0))
	{
		if (dup2(content->array_ptr->pipe[content->pos - 1][0], STDIN_FILENO) ==
			// PROTECTED
			-1)
		{
			content->error_code = 1;
			ft_dup2_pb(content, "pipe");
			ft_exit(content);
		}
	}
	if ((content->size > 1 && content->pos < content->size - 1))
	{
		if (dup2(content->array_ptr->pipe[content->pos][1], STDOUT_FILENO) ==
			// PROTECTED
			-1)
		{
			content->error_code = 1;
			ft_dup2_pb(content, "pipe");
			ft_exit(content);
		}
	}
}

int	ft_parse_redirections(t_content *content)
{
	content->infile = -2;
	content->outfile = -2;
	ft_deal_with_pipes(content);
	if (ft_deal_with_redir_child(content) == 1)
		ft_exit(content);
	return (0);
}
