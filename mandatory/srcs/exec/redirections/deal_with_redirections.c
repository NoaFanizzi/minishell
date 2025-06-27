/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:33:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/27 10:41:39 by nofanizz         ###   ########.fr       */
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

int	ft_deal_with_hdoc(t_content *content, size_t *i)
{
	int	h_fd;
	int temp_i;
	int	hdoc_count;
	char *line;
	
	hdoc_count = 0;
	while(*i < content->files->size && content->files[*i].type == HDOC)
	{
		if(content->files[*i].type == HDOC)
		{
			hdoc_count++;
			temp_i = content->files[*i].index + 1;
			h_fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
			ft_putstr_fd("> ", 1);
			line = get_next_line(0);
			while(line != NULL)
			{
				if(ft_strlen(line) == (ft_strlen(content->cmd_splitted[content->pos][temp_i]) + 1)
					&& ft_strncmp(line, content->cmd_splitted[content->pos][temp_i], ft_strlen(content->cmd_splitted[content->pos][temp_i])) == 0)
					break;
				ft_putstr_fd("> ", 1);
				ft_putstr_fd(line, h_fd);
				free(line);
				line = get_next_line(0);
			}
			free(line);
			close(h_fd); // je le close parce qu'il sert plus a rien
		}
		*i += 1;
	}
	if(hdoc_count != 0)
	{
		h_fd = open("temp", O_RDWR | O_CREAT | O_APPEND, 0644);
		dup2(h_fd, STDIN_FILENO); // je fais lire depuis le fichier temporaire creee
		close(h_fd); // je le close parce qu'il sert plus a rien
	}
	return(0);
}
