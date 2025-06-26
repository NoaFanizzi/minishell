/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_find.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:04:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/26 12:05:18 by nofanizz         ###   ########.fr       */
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
				//printf("ABERRANT= %s\n", content->cmd_splitted[content->pos][content->files[i].index + 1]);
				int	saved_out;
				int	h_fd;
				int temp_i;
				char *line;
				//char *test;
				size_t	i = 0;

				temp_i = content->files[i].index + 1;
				//printf("ABERRANT = %s\n", content->cmd_splitted[content->pos][temp_i]);
				saved_out = dup(1);
				h_fd = open("temp", O_RDWR | O_CREAT | O_APPEND, 0644);
				dup2(h_fd, STDOUT_FILENO);
				ft_putstr_fd("heredoc> ", saved_out);
				line = get_next_line(0);
				ft_putstr_fd("heredoc> ", saved_out);
				ft_putstr_fd(line, 1);
				while(line != NULL)
				{
					if(ft_strlen(line) == (ft_strlen(content->cmd_splitted[content->pos][temp_i]) + 1)
						&& ft_strncmp(line, content->cmd_splitted[content->pos][temp_i], ft_strlen(content->cmd_splitted[content->pos][temp_i])) == 0)
					{
						printf("AAAAAAAAAAAAAAAAAAAAA\n");
						break;
					}
					if(ft_strncmp(line, content->cmd_splitted[content->pos][temp_i], ft_strlen(content->cmd_splitted[content->pos][temp_i])) == 0)
						printf("same content\n");
					if(ft_strlen(line) == (ft_strlen(content->cmd_splitted[content->pos][temp_i]) + 1))
						printf("same length\n");
					//printf("line length = %zu\n", ft_strlen(line));
					//printf("eof length = %zu\n", ft_strlen(content->cmd_splitted[content->pos][temp_i]) + 1);
					//printf("line = %s\n", line);
					//printf("eof = %s\n", content->cmd_splitted[content->pos][temp_i]);
					// test = ft_itoa(ft_strlen(line));
					// ft_putstr_fd(test, 1);
					// free(test);
					free(line);
					line = get_next_line(0);
					ft_putstr_fd("heredoc> ", saved_out);
					ft_putstr_fd(line, 1);
				}
				free(line);
				dup2(saved_out, STDOUT_FILENO); // je remet sur la sortie standard;
				dup2(h_fd, STDIN_FILENO); // je fais lire depuis le fichier temporaire creee
				close(h_fd); // je le close parce qu'il sert plus arien
				ft_putstr_fd("on est a la fin et ca sort sur l'entree standard\n", STDOUT_FILENO);
				
				
				// dup2(saved_out, STDOUT_FILENO);
				// line = get_next_line(h_fd);
				// if(line)
				// 	ft_putstr_fd(line, STDOUT_FILENO);
				// while(line != NULL)
				// {
				// 	free(line);
				// 	get_next_line(line);
				// 	ft_putstr_fd(line, STDOUT_FILENO);
				// }
				// if(line)
				// 	free(line);
				// return;
			// 	printf("content->cmd :\n\n");
			// 	ft_display_tab(content->cmd);
			// 	printf("content->arg : \n\n");
			// 	ft_display_tab(content->arg);
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
