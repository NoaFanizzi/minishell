/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:33:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/06 15:57:57 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_deal_with_out(t_content *content, size_t i)
{
	size_t	position;

	position = 0;
	if(content->files[i].type == OUT)
	{
		position = content->pos;
		if(content->pos % 2 != 0)
			position += 1;
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
	size_t	position;

	position = 0;
	if(content->files[i].type == APND)
	{
		position = content->pos;
		if(content->pos % 2 != 0)
			position += 1;
		if(!(content->cmd_splitted[position][content->files[i].index + 1]))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", STDERR_FILENO);
			content->error_code = 2;
			return(O_ERROR);
		}
		content->outfile = open(content->cmd_splitted[position][content->files[i].index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
		if(content->outfile == -1)
			return(ft_open_error(content, content->cmd_splitted[position][content->files[i].index + 1]));
		if (dup2(content->outfile, STDOUT_FILENO) == -1)
			return(ft_dup2_pb (content, content->cmd_splitted[position][content->files[i].index + 1]));
		close(content->outfile);
		content->outfile = -2;
	}
	return(0);
}

int ft_deal_with_in(t_content *content, size_t i)
{
	int position;

	position = 0;
	if(content->files[i].type == IN)
	{
		position = content->pos;
		if(content->pos % 2 != 0)
			position += 1;
		if(!(content->cmd_splitted[position][content->files[i].index + 1]))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", STDERR_FILENO);
			content->error_code = 2;
			return(O_ERROR);
		}
		content->infile = open(content->cmd_splitted[position][content->files[i].index + 1], O_RDONLY, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
		if(content->infile == -1)
			return(ft_open_error(content, content->cmd_splitted[position][content->files[i].index + 1]));
		if (dup2(content->infile, STDIN_FILENO) == -1)
			return(ft_dup2_pb (content, content->cmd_splitted[position][content->files[i].index + 1]));
		close(content->infile);
		content->infile = -2;
	}
	return(0);
}

char *ft_get_temp_file(t_content *content)
{
	char *converted_pos;
	char *temp_file;
	
	converted_pos = ft_itoa(content->pos);
	temp_file = ft_strjoin("temp", converted_pos);
	free(converted_pos);
	return(temp_file);
}

int	ft_deal_with_hdoc(t_content *content, size_t *i)
{
	int temp_i;
	//int	hdoc_count;
	char *line;
	char *temp_file;
	char *expanded_line;
	int position;
		
	//hdoc_count = 0;
	position = 0;
	while(*i < content->files->size && content->files[*i].type == HDOC)
	{
		position = content->pos;
		if(content->pos % 2 != 0)
			position += 1;
		if(content->files[*i].type == HDOC)
		{
			//hdoc_count++;
			temp_i = content->files[*i].index + 1;
			temp_file = ft_get_temp_file(content);
			content->h_fd = open(temp_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			free(temp_file);
			//unlink("temp");
			if(content->h_fd == -1)
			{
				content->h_fd = -2;
				return(ft_open_error(content, "h_fd"));
			}
			ft_putstr_fd("> ", 1);
			line = get_next_line(0);
			while(line != NULL)
			{
				if(ft_strlen(line) == (ft_strlen(content->cmd_splitted[position][temp_i]) + 1)
					&& ft_strncmp(line, content->cmd_splitted[position][temp_i], ft_strlen(content->cmd_splitted[position][temp_i])) == 0)
					break;
				ft_putstr_fd("> ", 1);
				expanded_line = expand(line, content->env);
				ft_putstr_fd(expanded_line, content->h_fd);
				free(expanded_line);
				line = get_next_line(0);
			}
			free(line);
			close(content->h_fd); // je le close parce qu'il sert plus a rien
			content->h_fd = -2; // je le remet a -2 pour savoir si je dois close ou pas dans l'exit;
		}
		*i += 1;
	}
	return(0);
}
