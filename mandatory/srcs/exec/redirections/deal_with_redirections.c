/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:33:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/15 17:08:33 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_deal_with_out(t_content *content, size_t i)
{
	size_t	position;

	position = 0;
	if(content->files[i].type == OUT)
	{
		//dprintf(STDERR_FILENO, "one out found\n");
		position = content->pos;
		//dprintf(STDERR_FILENO, "content->files[i].pos BEFORE = %zu\n", position);
		if(content->pos != 0)
			position += position;
		//dprintf(STDERR_FILENO, "content->files[i].pos AFTER = %zu\n", position);
		//dprintf(STDERR_FILENO, "content->cmd_splitted[position][content->files[i].index + 2] = %s\n", content->cmd_splitted[position][content->files[i].index + 1]);
		if((content->cmd_splitted[position][content->files[i].index + 1]) == NULL)
		{
			//dprintf(STDERR_FILENO, "PROBLEMM\n");
			ft_putstr_fd("maxishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
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
		if(content->pos != 0)
			position += position;
		if(!(content->cmd_splitted[position][content->files[i].index + 1]))
		{
			ft_putstr_fd("maxishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
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
		if(content->pos != 0)
			position += position;
		if(!(content->cmd_splitted[position][content->files[i].index + 1]))
		{
			ft_putstr_fd("maxishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
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
	char *line;
	char *temp_file;
	char *expanded_line;
	int position;
	
	position = 0;
	content->stdin_saved = dup(STDIN_FILENO);
	while(*i < content->files->size && content->files[*i].type == HDOC)
	{
		position = content->pos;
		if(content->pos != 0)
			position += position;
		if(content->files[*i].type == HDOC)
		{
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
			
			while(1)
			{
				line = readline("> ");
				if(g_signal == SIGINT)
				{
					dup2(content->stdin_saved, STDIN_FILENO);
					free(line);
					temp_file = ft_get_temp_file(content);
					unlink(temp_file);
					free(temp_file);
					close(content->h_fd);
					close(content->stdin_saved);
					content->stdin_saved = -2;
					content->error_code = 130;
					g_signal = 0;
					return(1);
				}
				if(!line || ft_strcmp(line, content->cmd_splitted[position][temp_i]) == 0)
					break;
				expanded_line = expand(line, content->env);
				ft_putendl_fd(expanded_line, content->h_fd);
				free(expanded_line);
			}
			if(line)
				free(line);
			close(content->h_fd); // je le close parce qu'il sert plus a rien
			content->h_fd = -2; // je le remet a -2 pour savoir si je dois close ou pas dans l'exit;
		}
		*i += 1;
	}
	close(content->stdin_saved);
	content->stdin_saved = -2;
	return(0);
}
