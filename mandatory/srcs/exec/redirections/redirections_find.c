/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_find.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:04:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/03 11:45:33 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirections.h"

int	ft_use_hdoc(t_content *content, size_t i)
{
	char *temp_file;
	int position;

	position = 0;
	if(content->files[i].type == IN)
	{
		position = content->pos;
		if(content->pos % 2 != 0)
			position += 1;
		temp_file = ft_get_temp_file(content);
		content->infile = open("temp_file", O_RDONLY, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
		free(temp_file);
		if(content->infile == -1)
			return(ft_open_error(content, content->cmd_splitted[position][content->files[i].index + 1]));
		if (dup2(content->infile, STDIN_FILENO) == -1)
			return(ft_dup2_pb (content, content->cmd_splitted[position][content->files[i].index + 1]));
		close(content->infile);
		content->infile = -2;
	}
	return(0);
}

int	ft_deal_with_redir(t_content *content)
{
	size_t size;
	size_t	i;

	i = 0;
	if(content->files != NULL && &content->files[0] != NULL)
	{
		size = content->files[i].size;
		while(i < size)
		{
			if(ft_deal_with_out(content, i) == O_ERROR)
				return(1);
			if(ft_deal_with_apnd(content, i) == O_ERROR)
				return(1);
			if(ft_deal_with_in(content, i) == O_ERROR)
				return(1);
			if(ft_use_hdoc(content, i) == O_ERROR)
				return(1);
			i++;
		}
	}
	return(0);
}

void	ft_deal_with_pipes(t_content *content)
{
	if((content->size > 1 && content->pos > 0))
	{	
		if (dup2(content->array_ptr->pipe[content->pos - 1][0], STDIN_FILENO) == -1)
		{
			ft_dup2_pb (content, "pipe");
		}
	}
	if((content->size > 1 && content->pos < content->size - 1))
	{
		if (dup2(content->array_ptr->pipe[content->pos][1], STDOUT_FILENO) == -1)
			ft_dup2_pb (content, "pipe");
	}
}

int	ft_parse_redirections(t_content *content)
{
	content->infile = -2;
	content->outfile = -2;
	ft_deal_with_pipes(content);
	if(ft_deal_with_redir(content) == 1)
		ft_exit(content);
	return(0);
}
