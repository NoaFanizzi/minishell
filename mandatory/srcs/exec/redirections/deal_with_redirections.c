/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:33:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/23 16:00:44 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_deal_with_out(t_content *content, size_t i)
{
	size_t	position;

	position = 0;
	if(content->files[i].type == OUT)
	{
		dprintf(STDERR_FILENO, "Entered in deal_with_out\n");
		position = content->pos;
		if(content->pos != 0)
			position += position;
		if((content->cmd_splitted[position][content->files[i].index + 1]) == NULL)
		{
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
		dprintf(STDERR_FILENO, "Entered in deal_with_apnd\n");
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
		dprintf(STDERR_FILENO, "Entered in deal_with_in\n");
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

int	ft_is_printable(char c)
{
	if(c >= 32 && c <= 126)
		return(0);
	return(1);
}

char *ft_get_temp_file(void)
{
	char *random_file;
	int random_fd;
	char *temp_file;
	size_t	i;
	size_t	j;
	
	//converted_pos = ft_itoa(pos);
	j = 0;
	random_file = ft_calloc(6, sizeof(char));
	random_fd = open("/dev/random", O_RDONLY);
	while(j < 5)
	{
		i = 0;
		temp_file = get_next_line(random_fd);
		while(temp_file[i] && j < 5)
		{
			if(ft_isalpha(temp_file[i]) == 1)
			{
				random_file[j] = temp_file[i];
				j++;
			}
			if(j == 5 || !temp_file)
				break;
			i++;
		}
		free(temp_file);
		temp_file = NULL;
	}
	if(temp_file)
		free(temp_file);
	random_file[5] = '\0';
	close(random_fd);
	return(random_file);
}

void	add_new_fd_in_array(t_content *content)
{
	size_t	i;

	i = 0;
	while(content->fd_array[i] != -8 && i < FD_SETSIZE)
		i++;
	if(i == FD_SETSIZE)
	{
		//TODO Jsp quoi faire et faut aussi que je set le exit_code
		ft_putstr_fd("maxishell: too much fd opened", STDERR_FILENO);
	}
	content->fd_array[i] = content->h_fd;
}

void	ft_close_open(t_content *content, char *temp_file)
{
	int old_fd;
	size_t	i;

	i = 0;
	old_fd = content->h_fd;
	close(content->h_fd);
	content->h_fd = open(temp_file, O_RDWR | O_CREAT ,0644);
	while(content->fd_array[i] != old_fd)
		i++;
	content->fd_array[i] =content->h_fd;
	
}

int	ft_deal_with_hdoc(t_content *content, size_t *i)
{
	int temp_i;
	char *line;
	char *temp_file;
	char *expanded_line;
	int position;
	size_t suff_temp;
	
	position = 0;
	temp_file = NULL;
	content->stdin_saved = dup(STDIN_FILENO);
	while(*i < content->files->size && content->files[*i].type == HDOC)
	{
		position = content->pos;
		if(content->pos != 0)
			position += position;
		if(content->files[*i].type == HDOC)
		{
			suff_temp = 0;
			temp_i = content->files[*i].index + 1;
			temp_file = ft_get_temp_file();
			content->h_fd = open(temp_file, O_RDWR | O_CREAT, 0644);
			add_new_fd_in_array(content);
			*i += 1;
			content->array_ptr->hdoc_length += *i;
			while(1)
			{
				line = readline("> ");
				if(g_signal == SIGINT)
				{
					dup2(content->stdin_saved, STDIN_FILENO);
					free(line);
					close(content->h_fd);
					content->h_fd = -1;
					if(content->h_fd != -1)
						close(content->h_fd);
					close(content->stdin_saved);
					content->stdin_saved = -2;
					content->array_ptr->p_exit_status = 130;
					g_signal = 0;
					content->h_fd = -2;
					return(1);
				}
				if(!line || ft_strcmp(line, content->cmd_splitted[position][temp_i]) == 0)
					break;
				expanded_line = expand_word(line, content->env, content->array_ptr);
				ft_putendl_fd(expanded_line, content->h_fd);
				free(expanded_line);
			}
			if(line)
				free(line);
			//content->h_fd = -2; // je le remet a -2 pour savoir si je dois close ou pas dans l'exit;
		}
		ft_close_open(content, temp_file);
		unlink(temp_file);
		free(temp_file);
	}
	close(content->stdin_saved);
	content->stdin_saved = -2;
	return(0);
}
// @$#W%$E^%XR&C^UTYG
