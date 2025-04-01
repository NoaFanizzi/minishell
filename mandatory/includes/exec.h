/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:01:00 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/01 14:33:19 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "structs.h"
# include "minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>


void		free_tab(char **str);
void		ft_strcpy(char *dest, char *src);
void		ft_strcat(char *dest, char *src);
size_t		ct_count_size(char *str);
char		**ct_get_paths(char **env);
int 		ft_is_command(t_expar *expar, t_content *content,  char **env);
void		ft_close_all(t_expar *expar);
void		ft_dup2_pb(t_expar *expar, t_content *content);
int			ft_check_if_command(char *cmd, char *path);
void		ft_init_exec(char **env, t_array *array);
void		ft_exec_failure(t_expar *expar, int i);
void		ft_exec_cmd(t_expar *expar, t_content *content, char **env);




#endif