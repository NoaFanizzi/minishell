/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:33:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/26 12:05:08 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_deal_with_out(t_content *content, size_t i)
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
			ft_dup2_pb (content);
		close(content->outfile);
	}
	return(0);
}

int ft_deal_with_apnd(t_content *content, size_t i)
{
	if(content->files[i].type == APND)
	{
		content->outfile = open(content->cmd_splitted[content->pos][content->files[i].index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
		if(content->outfile == -1)
		{
			perror(content->cmd_splitted[content->pos][content->files[i].index + 1]);
			return(O_ERROR); //fait les trucs
		}
		if (content->expar != NULL && dup2(content->outfile, STDOUT_FILENO) == -1)
			ft_dup2_pb (content);
		close(content->outfile);
	}
	return(0);
}

int ft_deal_with_in(t_content *content, size_t i)
{
	if(content->files[i].type == IN)
	{
		content->infile = open(content->cmd_splitted[content->pos][content->files[i].index + 1], O_RDONLY, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
		if(content->infile == -1)
		{
			perror(content->cmd_splitted[content->pos][content->files[i].index + 1]);
			return(O_ERROR); //fait les trucs
		}
		if (content->expar != NULL && dup2(content->infile, STDIN_FILENO) == -1)
			ft_dup2_pb (content);
		close(content->infile);
	}
	return(0);
}
