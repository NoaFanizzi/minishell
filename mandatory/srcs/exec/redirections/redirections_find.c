/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_find.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:04:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/19 15:56:58 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirections.h"


int	ft_parse_redirections(t_content *content, t_expar *expar)
{
	size_t	i;
	//int	type;
	size_t size;

	i = 0;
	//type = -1;
	content->infile = -2;
	content->outfile = -2;
	if(&content->files[0] != NULL)
	{
		size = content->files[i].size;
		while(i < size)
		{
			if(content->files[i].type == OUT)
			{
				if(content->outfile != -2)
					close(content->outfile);
				//printf("outfile = %s\n",content->cmd_splitted[content->pos][content->files[i].index + 1]);
				content->outfile = open(content->cmd_splitted[content->pos][content->files[i].index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
				if(content->outfile == -1)
				{
					perror(content->cmd_splitted[content->pos][content->files[i].index + 1]);
					return(O_ERROR); //fait les trucs
				}
				if (dup2(content->outfile, STDOUT_FILENO) == -1)
					ft_dup2_pb (expar, content);
				close(content->outfile);
			}
			if(content->files[i].type == APND)
			{
				if(content->outfile != -2)
					close(content->outfile);
				content->outfile = open(content->cmd_splitted[content->pos][content->files[i].index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
				if(content->outfile == -1)
				{
					perror(content->cmd_splitted[content->pos][content->files[i].index + 1]);
					return(O_ERROR); //fait les trucs
				}
				if (dup2(content->outfile, STDOUT_FILENO) == -1)
					ft_dup2_pb (expar, content);
				close(content->outfile);
			}
			if(content->files[i].type == IN)
			{
				if(content->infile != -2)
					close(content->infile);
				content->infile = open(content->cmd_splitted[content->pos][content->files[i].index + 1], O_WRONLY, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
				if(content->infile == -1)
				{
					perror(content->cmd_splitted[content->pos][content->files[i].index + 1]);
					return(O_ERROR); //fait les trucs
				}
				if (dup2(content->infile, STDIN_FILENO) == -1)
					ft_dup2_pb (expar, content);
				close(content->infile);
			}
			i++;
		}
	}
	if(content->infile == -2)
	{
		if(content->size > 1 && content->pos != content->size - 1)
		{
			if (dup2(expar->pipe[0], STDIN_FILENO) == -1)
				ft_dup2_pb (expar, content);
			close(expar->pipe[0]);
		}
	}
	if(content->outfile == -2)
	{
		if(content->size > 1 && content->pos != content->size - 1)
		{
			if (dup2(expar->pipe[1], STDOUT_FILENO) == -1)
				ft_dup2_pb (expar, content);
			close(expar->pipe[1]);
		}
	}
	return(0);
}
