/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:33:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/02 18:29:35 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_error(t_content *content, char *str)
{
	ft_putstr_fd("maxishell: ", STDERR_FILENO);
	perror(str);
	content->error_code = 1;
	return(O_ERROR);
}

int ft_deal_with_out(t_content *content, size_t i)
{
	size_t	position;

	position = 0;
	if(content->files[i].type == OUT)
	{
		ft_putstr_fd("\n", 1);
		position = content->pos;
		if(content->pos % 2 != 0)
			position += 1;
		printf("position = %zu\n", position);
		ft_display_tab(content->cmd_splitted[position]);
		//printf("content = %s\n", content->cmd_splitted[content->pos][content->files[i].index]);

		if((content->cmd_splitted[position][content->files[i].index + 1]) == NULL)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", STDERR_FILENO);
			content->error_code = 2;
			return(O_ERROR);
		}
		content->outfile = open(content->cmd_splitted[position][content->files[i].index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
		if(content->outfile == -1)
			return(ft_open_error(content, content->cmd_splitted[position][content->files[i].index + 1]));
		if (dup2(content->outfile, STDOUT_FILENO) == -1)
			return(ft_dup2_pb (content, content->cmd_splitted[position][content->files[i].index + 1]));
		close(content->outfile);
		content->outfile = -2;
	}
	return(0);
}

int ft_deal_with_apnd(t_content *content, size_t i)
{
	if(content->files[i].type == APND)
	{
		if(!(content->cmd_splitted[content->pos][content->files[i].index + 1]))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", STDERR_FILENO);
			content->error_code = 2;
			return(O_ERROR);
		}
		content->outfile = open(content->cmd_splitted[content->pos][content->files[i].index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
		if(content->outfile == -1)
			return(ft_open_error(content, content->cmd_splitted[content->pos][content->files[i].index + 1]));
		if (content->expar != NULL && dup2(content->outfile, STDOUT_FILENO) == -1)
			return(ft_dup2_pb (content, content->cmd_splitted[content->pos][content->files[i].index + 1]));
		close(content->outfile);
		content->outfile = -2;

	}
	return(0);
}

int ft_deal_with_in(t_content *content, size_t i)
{
	if(content->files[i].type == IN)
	{
		if(!(content->cmd_splitted[content->pos][content->files[i].index + 1]))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", STDERR_FILENO);
			content->error_code = 2;
			return(O_ERROR);
		}
		content->infile = open(content->cmd_splitted[content->pos][content->files[i].index + 1], O_RDONLY, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
		if(content->infile == -1)
			return(ft_open_error(content, content->cmd_splitted[content->pos][content->files[i].index + 1]));
		if (content->expar != NULL && dup2(content->infile, STDIN_FILENO) == -1)
			ft_dup2_pb (content, content->cmd_splitted[content->pos][content->files[i].index + 1]);
		close(content->infile);
		content->infile = -2;
	}
	return(0);
}

int	ft_deal_with_hdoc(t_content *content, size_t *i)
{
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
			content->h_fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
			if(content->h_fd == -1)
			{
				ft_putstr_fd("maxishell: ", STDERR_FILENO);
				perror("temp");
				content->error_code = 1;
				content->h_fd = -2; // je le remet a -2 pour savoir si je dois close ou pas dans l'exit;
				return(O_ERROR);
			}
			ft_putstr_fd("> ", 1);
			line = get_next_line(0);
			while(line != NULL)
			{
				if(ft_strlen(line) == (ft_strlen(content->cmd_splitted[content->pos][temp_i]) + 1)
					&& ft_strncmp(line, content->cmd_splitted[content->pos][temp_i], ft_strlen(content->cmd_splitted[content->pos][temp_i])) == 0)
					break;
				ft_putstr_fd("> ", 1);
				ft_putstr_fd(line, content->h_fd);
				free(line);
				line = get_next_line(0);
			}
			free(line);
			close(content->h_fd); // je le close parce qu'il sert plus a rien
			content->h_fd = -2; // je le remet a -2 pour savoir si je dois close ou pas dans l'exit;
		}
		*i += 1;
	}
	if(hdoc_count != 0)
	{
		content->h_fd = open("temp", O_RDWR | O_CREAT | O_APPEND, 0644);
		dup2(content->h_fd, STDIN_FILENO); // je fais lire depuis le fichier temporaire creee
		close(content->h_fd); // je le close parce qu'il sert plus a rien
	}
	return(0);
}
