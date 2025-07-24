/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:33:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/24 16:22:36 by nofanizz         ###   ########.fr       */
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
		if(content->pos != 0)
			position += position;
		if((content->cmd_splitted[position][content->files[i].index + 1]) == NULL)
		{
			ft_putstr_fd("maxishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
			content->error_code = 2;
			return(O_ERROR);
		}
		content->outfile = open(content->cmd_splitted[position][content->files[i].index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644); //PROTECTED
		if(content->outfile == -1)
			return(ft_open_error(content, content->cmd_splitted[position][content->files[i].index + 1]));
		if (dup2(content->outfile, STDOUT_FILENO) == -1) //PROTECTED
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
		content->outfile = open(content->cmd_splitted[position][content->files[i].index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644); //PROTECTED
		if(content->outfile == -1)
			return(ft_open_error(content, content->cmd_splitted[position][content->files[i].index + 1]));
		if (dup2(content->outfile, STDOUT_FILENO) == -1) //PROTECTED
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
		content->infile = open(content->cmd_splitted[position][content->files[i].index + 1], O_RDONLY, 0644); //PROTECTED
		if(content->infile == -1)
			return(ft_open_error(content, content->cmd_splitted[position][content->files[i].index + 1]));
		if (dup2(content->infile, STDIN_FILENO) == -1) //PROTECTED
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

int ft_get_temp_file(char **random_file, t_content *content)
{
	int random_fd;
	char *temp_file;
	size_t i;
	size_t j;

	j = 0;
	*random_file = ft_calloc(6, sizeof(char)); //PROTECTED
	if (!*random_file)
		return (ft_open_error(content, "random_file"));
	random_fd = open("/dev/random", O_RDONLY); //PROTECTED
	if (random_fd == -1)
	{
		free(*random_file);
		return (ft_open_error(content, "/dev/random"));
	}

	while (j < 5)
	{
		i = 0;
		temp_file = get_next_line(random_fd);
		if (!temp_file) // en cas de fin ou erreur
			break;
		while (temp_file[i] && j < 5)
		{
			if (ft_isalpha(temp_file[i]) == 1)
			{
				(*random_file)[j] = temp_file[i];
				j++;
			}
			i++;
		}
		free(temp_file);
	}
	(*random_file)[5] = '\0';
	close(random_fd);
	return (0);
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
	content->h_fd = open(temp_file, O_RDONLY | O_CREAT ,0644);
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
	if(content->stdin_saved == -1)
		return(ft_dup2_pb(&content->array_ptr->content[0], "stdin"));
	while(*i < content->files->size && content->files[*i].type == HDOC)
	{
		position = content->pos;
		if(content->pos != 0)
			position += position;
		if(content->files[*i].type == HDOC)
		{
			suff_temp = 0;
			temp_i = content->files[*i].index + 1;
			if(ft_get_temp_file(&temp_file, content) == O_ERROR) // PROTECTED
				return(1);
			content->h_fd = open(temp_file, O_RDWR | O_CREAT, 0644); // PROTECTED
			if(content->h_fd == -1)
			{
				content->h_fd = -2;
				free(temp_file);
				return(ft_open_error(content, "content->h_fd"));
			}
			add_new_fd_in_array(content);
			*i += 1;
			content->array_ptr->hdoc_length += *i;
			while(1)
			{
				line = readline("> ");
				if (!line)
				{
					unlink(temp_file);
					free(temp_file);
					if(dup2(content->stdin_saved, STDIN_FILENO) == -1) // PROTECTED
						return(ft_dup2_pb(content, "content->stdin_saved"));
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
				if(g_signal == SIGINT)
				{
					unlink(temp_file);
					free(temp_file);
					if(dup2(content->stdin_saved, STDIN_FILENO) == -1) // PROTECTED
						return(ft_dup2_pb(content, "content->stdin_saved"));
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
				expanded_line = expand_word(line, content->env, content->array_ptr); // PROTECTED
				if(!expanded_line)
				{
					free(temp_file);
					return(ft_open_error(content, "expanded_line"));
				}
				ft_putendl_fd(expanded_line, content->h_fd);
				free(expanded_line);
			}
			if(line)
				free(line);
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
