/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_find.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:04:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/25 14:34:07 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirections.h"


void	ft_deal_with_redir(t_content *content, t_expar *expar)
{
	size_t size;
	size_t	i;

	i = 0;	
	if(content->files != NULL && &content->files[0] != NULL)
	{
		size = content->files[i].size;
		while(i < size)
		{
			ft_deal_with_out(content, expar, i);
			ft_deal_with_apnd(content, expar, i);
			ft_deal_with_in(content, expar, i);
			
			
			// if(content->files[i].type == HDOC)
			// {
			// 	// int	saved_out;
			// 	// int	h_fd;
			// 	// char *line;

			// 	// saved_out = dup(1);
			// 	// h_fd = open("temp", O_RDWR | O_CREAT | O_APPEND, 0644);
			// 	// dup2(h_fd, STDOUT_FILENO);
			// 	// line = get_next_line(0);
			// 	// ft_putstr_fd(line, 1);
			// 	// while(line != NULL)
			// 	// {
			// 	// 	free(line);
			// 	// 	line = get_next_line(0);
			// 	// 	ft_putstr_fd(line, 1);
			// 	// }
			// 	// free(line);
			// 	// printf("content->cmd :\n\n");
			// 	// ft_display_tab(content->cmd);
			// 	// printf("content->arg : \n\n");
			// 	// ft_display_tab(content->arg);
			// }
			i++;
		}
	}
}

void	ft_deal_with_pipes(t_content *content, t_expar *expar)
{
	if((content->size > 1 && content->pos > 0))
	{	
		if (dup2(expar->pipe[content->pos - 1][0], STDIN_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
	if((content->size > 1 && content->pos < content->size - 1))
	{
		if (dup2(expar->pipe[content->pos][1], STDOUT_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
}

int	ft_parse_redirections(t_content *content, t_expar *expar)
{
	content->infile = -2;
	content->outfile = -2;
	ft_deal_with_pipes(content, expar);
	ft_deal_with_redir(content, expar);
	return(0);
}
