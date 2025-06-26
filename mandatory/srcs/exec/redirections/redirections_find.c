/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_find.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:04:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/26 15:01:53 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirections.h"


void	ft_deal_with_redir(t_content *content)
{
	size_t size;
	size_t	i;

	i = 0;	
	if(content->files != NULL && &content->files[0] != NULL)
	{
		size = content->files[i].size;
		while(i < size)
		{
			ft_deal_with_out(content, i);
			ft_deal_with_apnd(content, i);
			ft_deal_with_in(content, i);
			
			if(content->files[i].type == HDOC)
			{
				int	h_fd;
				int temp_i;
				char *line;
				size_t	i = 0;

				temp_i = content->files[i].index + 1;
				h_fd = open("temp", O_RDWR | O_CREAT | O_APPEND, 0644);
				ft_putstr_fd("> ", 1);
				line = get_next_line(0);
				while(line != NULL)
				{
					if(ft_strlen(line) == (ft_strlen(content->cmd_splitted[content->pos][temp_i]) + 1)
						&& ft_strncmp(line, content->cmd_splitted[content->pos][temp_i], ft_strlen(content->cmd_splitted[content->pos][temp_i])) == 0)
						break;
					ft_putstr_fd("> ", 1);
					ft_putstr_fd(line, h_fd);
					// if(ft_strncmp(line, content->cmd_splitted[content->pos][temp_i], ft_strlen(content->cmd_splitted[content->pos][temp_i])) == 0)
					// 	printf("same content\n");
					// if(ft_strlen(line) == (ft_strlen(content->cmd_splitted[content->pos][temp_i]) + 1))
					// 	printf("same length\n");
					free(line);
					line = get_next_line(0);
				}
				free(line);
				close(h_fd); // je le close parce qu'il sert plus a rien
				h_fd = open("temp", O_RDWR | O_CREAT | O_APPEND, 0644);
				dup2(h_fd, STDIN_FILENO); // je fais lire depuis le fichier temporaire creee
				close(h_fd); // je le close parce qu'il sert plus a rien

				//ft_putstr_fd("on est a la fin et ca sort sur l'entree standard\n", STDOUT_FILENO);
			}
			i++;
		}
	}
}

void	ft_deal_with_pipes(t_content *content)
{
	if((content->size > 1 && content->pos > 0))
	{	
		if (dup2(content->array_ptr->pipe[content->pos - 1][0], STDIN_FILENO) == -1)
		{
			ft_dup2_pb (content);
		}
	}
	if((content->size > 1 && content->pos < content->size - 1))
	{
		if (dup2(content->array_ptr->pipe[content->pos][1], STDOUT_FILENO) == -1)
			ft_dup2_pb (content);
	}
}

int	ft_parse_redirections(t_content *content)
{
	content->infile = -2;
	content->outfile = -2;
	ft_deal_with_pipes(content);
	ft_deal_with_redir(content);
	return(0);
}
