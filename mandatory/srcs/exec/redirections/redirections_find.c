/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_find.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:04:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/27 10:34:20 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirections.h"


void	ft_deal_with_redir(t_content *content)
{
	size_t size;
	size_t	i;

	i = 0;	
	if(content->files != NULL && &content->files[0] != NULL)
	{
		size = content->files[i].size;
		while(i < size)
		{
			ft_deal_with_out(content, i);
			ft_deal_with_apnd(content, i);
			ft_deal_with_in(content, i);
			ft_deal_with_hdoc(content, &i);
			i++;
		}
	}
}

void	ft_deal_with_pipes(t_content *content)
{
	if((content->size > 1 && content->pos > 0))
	{	
		if (dup2(content->array_ptr->pipe[content->pos - 1][0], STDIN_FILENO) == -1)
		{
			ft_dup2_pb (content);
		}
	}
	if((content->size > 1 && content->pos < content->size - 1))
	{
		if (dup2(content->array_ptr->pipe[content->pos][1], STDOUT_FILENO) == -1)
			ft_dup2_pb (content);
	}
}

int	ft_parse_redirections(t_content *content)
{
	content->infile = -2;
	content->outfile = -2;
	ft_deal_with_pipes(content);
	ft_deal_with_redir(content);
	return(0);
}
