/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:01:00 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/01 12:54:25 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "libft.h"
# include "structs.h"
# include "minishell.h"
# include "parsing.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include "redirections.h"
#include "get_next_line.h"
#include <errno.h>


void		free_tab(char **str);
void		ft_strcpy(char *dest, char *src);
void		ft_strcat(char *dest, char *src);
size_t		ct_count_size(char *str);
char		**ct_get_paths(t_list *var);
int 		ft_is_command(t_content *content);
void		ft_close_all(t_content *content);
void		ft_dup2_pb(t_content *content);
int			ft_check_if_command(char *cmd, char **path);
void		ft_init_exec(t_list **env, t_array *array);
void		ft_exec_failure(t_expar *expar, int i);
void		ft_exec_cmd(t_content *content, t_list **env);
char		**ft_convert_env(t_list *env);
void 		ft_free_array_content(t_array *array);
t_env		*ft_add_new_link(char *env);
int			ft_is_chr(char *str, char c);

//export.c
t_env *fill_env_arg(t_env **link, char *env, size_t *var_len);
int		ft_export(t_list **env, t_content *content);
int	ft_check_if_in_base(t_list *env, char *str);

//export_dup.c
t_list *dup_env_list(t_list *env);

//unset.c
int	ft_unset(t_list **env, t_content *content);
void	ft_free_link(void *link);

//init_exec.c
int	ft_is_built_in(t_content *content);
void	ft_close_pipes(t_array *array);

//exec_free
char **ft_cmd_join(char **a, char **b);

//unset.c
void	ft_rm_first_link(t_list **env);
void	ft_rm_link(t_list **env, int pos);

//exit.c
void	ft_exit(t_content *content);

size_t	ft_tablen(char **tab);


#endif