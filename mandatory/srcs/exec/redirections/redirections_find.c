/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_find.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:04:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/23 18:02:03 by nofanizz         ###   ########.fr       */
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

	if((content->size > 1 && content->pos > 0))
	{	
		//printf("IN\n");
		//printf("content->cmd = %s\n", content->cmd[0]);
		//printf("content->pos = %d\n", content->pos);
		if (dup2(expar->pipe[content->pos - 1][0], STDIN_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
		//printf("content->pos = %d\n", content->pos);
		//printf("content->size = %d\n", content->size);
		//printf("content->cmd = %s\n", content->cmd[0]);
		//printf("content->pos = %d\n", content->pos);
	if((content->size > 1 && content->pos < content->size - 1))
	{
		//printf("OUT\n");
		//printf("content->cmd = %s\n", content->cmd[0]);
		//printf("content->pos = %d\n", content->pos);
		if (dup2(expar->pipe[content->pos][1], STDOUT_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}

	if(content->files != NULL && &content->files[0] != NULL)
	{
		//printf("nooooooooooooooooooon");
		size = content->files[i].size;
		while(i < size)
		{
			if(content->files[i].type == OUT)
			{
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
				content->outfile = open(content->cmd_splitted[content->pos][content->files[i].index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
				if(content->outfile == -1)
				{
					perror(content->cmd_splitted[content->pos][content->files[i].index + 1]);
					return(O_ERROR); //fait les trucs
				}
				if (expar != NULL && dup2(content->outfile, STDOUT_FILENO) == -1)
					ft_dup2_pb (expar, content);
				close(content->outfile);
			}
			if(content->files[i].type == IN)
			{
				content->infile = open(content->cmd_splitted[content->pos][content->files[i].index + 1], O_RDONLY, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
				if(content->infile == -1)
				{
					perror(content->cmd_splitted[content->pos][content->files[i].index + 1]);
					return(O_ERROR); //fait les trucs
				}
				if (expar != NULL && dup2(content->infile, STDIN_FILENO) == -1)
					ft_dup2_pb (expar, content);
				close(content->infile);
			}
			i++;
		}
	}

	return(0);
}
