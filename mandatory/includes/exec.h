/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:01:00 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/15 14:47:05 by nofanizz         ###   ########.fr       */
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
#include "built_in.h"
#include "get_next_line.h"
#include <errno.h>


//NOTHING
void	ft_display_tab(char **tab);
void	ft_free_tab(char **tab);
size_t	ft_tablen(char **tab);
void	ft_free_env(t_list *env);
void	ft_free_files(t_content *content);
void	ft_free_array_content(t_array *array);
void	ft_free_content(t_content *content);
void	ft_close_all(t_content *content);

//----------------------------BUILT-IN-----------------------------------------



//----------------------------CHILDREN-----------------------------------------

//children_built_in_dealing.c
int		ft_is_built_in_child(t_content *content, t_list **env);

//children_command.c
int		ft_check_if_command(char *cmd, char **path);
int		ft_is_command(t_content *content);

//children_process.c
int		ft_load_expar(t_content *content, t_list **env);
int		ft_prepare_execution(t_content *content, t_list **env);
void	ft_exec_cmd(t_content *content, t_list **env);

//errors_handling

//error_handling_error_code.c
void	ft_free_after_error(t_expar *expar, t_content *content, t_list **env, t_array *array);

//----------------------------PARENTS-----------------------------------------


//parents_built_in.c
void	ft_is_built_in_dad(t_array *array, t_list **env);
int		ft_is_built_in(t_content *content);

//parents_get_redirections.c
int		ft_get_redir_dad(t_array *array, t_list **env);

//parents_process.c
void	ft_wait_pid(t_array *array);
void	ft_load_preliminary_infos(t_list **env, t_array *array);
void	ft_init_exec(t_list **env, t_array *array);
int     ft_process_here_doc(t_array *array);


//----------------------------PIPES-----------------------------------------

//pipes_dealing.c
void	ft_init_pipe(t_array *array);
void	ft_close_pipes(t_array *array);

//----------------------------REDIRECTIONS-----------------------------------------

//deal_with_redirections.c
int		ft_deal_with_out(t_content *content, size_t i);
int		ft_deal_with_apnd(t_content *content, size_t i);
int		ft_deal_with_in(t_content *content, size_t i);
int		ft_deal_with_hdoc(t_content *content, size_t *i);

//redirections_find.c
int		ft_deal_with_redir(t_content *content);
void	ft_deal_with_pipes(t_content *content);
int		ft_parse_redirections(t_content *content);

//----------------------------UTILS-----------------------------------------

//exec_env_converted.c
size_t	ft_env_length(t_list *env);
int	ft_add_new_tab(t_list *env, char **converted, size_t i);
char	**ft_convert_env(t_list *env);

//exec_free.c
int	ft_dup2_pb(t_content *content, char *str);
void	ft_exec_failure(t_expar *expar, int i);

//exec_utils.c
void	ft_strcpy(char *dest, char *src);
void	ft_strcat(char *dest, char *src);
char	**ct_get_paths(t_list *var, t_content *content);
char **ft_cmd_join(char **a, char **b);
void	ft_display_array_content(t_array *array);

//----------------------------ERROR-----------------------------------------

//error_handling.c
int	ft_open_error(t_content *content, char *str);
int	ft_dup2_pb(t_content *content, char *str);








#endif