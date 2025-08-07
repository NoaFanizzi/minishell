/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:01:00 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/07 20:05:20 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "built_in.h"
# include <errno.h>

void	ft_display_int_array(t_array *array);

// NOTHING
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

// children_built_in_dealing.c
int		ft_is_built_in_child(t_content *content, t_list **env);

// children_command.c
int		ft_is_command(t_content *content);
void	check_f_ok(t_content *content, char *path);
void	check_exist(t_content *content, char *path);
int		ft_is_path_command(t_content *content);
int		check_command_validity(t_content *content, size_t i);
int		check_validity_in_dir(t_content *content);

// children_process.c
int		ft_load_expar(t_content *content, t_list **env);
int		ft_prepare_execution(t_content *content, t_list **env);
void	ft_exec_cmd(t_content *content, t_list **env);
void	child_management(t_list **env, t_array *array);

// errors_handling

// error_handling_error_code.c
void	ft_free_after_error(t_expar *expar, t_content *content, t_list **env,
			t_array *array);

//----------------------------PARENTS-----------------------------------------

// parents_built_in.c
int		ft_is_built_in_dad(t_array *array, t_list **env);
int		ft_is_built_in(t_content *content);

// parents_get_redirections.c
int		ft_get_redir_dad(t_array *array, t_list **env);

// parents_process.c
void	ft_wait_pid(t_array *array, size_t length);
int		ft_load_preliminary_infos(t_list **env, t_array *array);
void	ft_init_exec(t_list **env, t_array *array);
int		ft_process_here_doc(t_array *array);
int		count_hdoc(t_content *content);

//----------------------------PIPES-----------------------------------------

// pipes_dealing.c
int		ft_init_pipe(t_array *array);
void	ft_close_pipes(t_array *array, size_t length);

//----------------------------REDIRECTIONS----------------------------------

// deal_with_redirections.c
int		ft_is_printable(char c);
int		ft_deal_with_apnd(t_content *content, size_t i);

// in.c
int		check_in(t_content *content, size_t i, size_t position);
int		ft_deal_with_in(t_content *content, size_t i);

// out.c
int		check_out(t_content *content, size_t i, size_t position);
int		ft_deal_with_out(t_content *content, size_t i);

// redirections_find.c
int		ft_deal_with_redir_parents(t_content *content);
int		ft_deal_with_redir_child(t_content *content);
void	ft_deal_with_pipes(t_content *content);
int		ft_parse_redirections(t_content *content);

// here_doc_parents.c
int		controld_hdoc_dealing(char *line, t_content *content, int *data,
			char *temp_file);
int		sigint_hdoc_dealing(t_content *content, char *temp_file, char *line);
int		ft_launch_here_doc(t_content *content, int *data, char *temp_file);
int		prepare_hdoc(t_content *content, size_t *i, char *temp_file);
int		ft_deal_with_hdoc(t_content *content, size_t *i);

// here_doc_child.c
int		get_hdoc_fd(t_content *content);
int		ft_use_hdoc(t_content *content, size_t i);
int		loop_hdoc(t_array *array, size_t size, size_t i);
int		ft_process_here_doc(t_array *array);
int		h_expansion(char *line, t_content *content, char *temp_file);

// here_doc_signals.c
int		controld_hdoc_dealing(char *line, t_content *content, int *data,
			char *temp_file);
int		get_stdin(t_content *content);
int		sigint_hdoc_dealing(t_content *content, char *temp_file, char *line);

// temp_file_generation.c
void	ft_load_temp_file(int random_fd, char **random_file);
int		ft_get_temp_file(char **random_file, t_content *content);

// check_dir_availability
void	check_exist(t_content *content, char *path);

//----------------------------UTILS-----------------------------------------

// exec_env_converted.c
size_t	ft_env_length(t_list *env);
int		ft_add_new_tab(t_list *env, char **converted, size_t i);
char	**ft_convert_env(t_list *env);

// exec_free.c
void	ft_exec_failure(t_expar *expar, int i);
void	*ft_free_one_chain_element(t_env *env, t_array *array);
void	free_unlink(char **str);

// exec_utils.c
char	**ct_get_paths(t_list *var, t_content *content);
char	**ft_cmd_join(char **a, char **b, t_content *content);
void	ft_display_array_content(t_array *array);
int		is_a_saved_pwd(t_content *content, char **dir, char **saved_pwd);
int		ft_contains_dir(char *path);
void	ft_display_env(t_list *env, t_content *content);

// exec_utils_2.c
void	add_new_fd_in_array(t_content *content);
int		ft_close_open(t_content *content, char *temp_file);
void	ft_close_in_out_saved(t_content *content);
void	ft_close_std(t_content *content);
void	ft_close_all(t_content *content);

// exec_utils_3.c
int		check_long_min_max(char *str, size_t *i);
void	ft_fill_array(int *tab);
void	check_directory_before_exec(t_content *content);

// exec_utils_free.c
int		load_cmd_tab(char ***a, char ***b, t_content *content, char ***cmd);
int		load_cmd_a(char ***a, t_content *content, char ***cmd, size_t *i);
void	ft_free_tab_length(char **tab, size_t length);

// display_header.c
void	display_header(void);

//----------------------------ERROR-----------------------------------------

// error_handling.c
int		ft_open_error(t_content *content, char *str);
int		ft_dup2_pb(t_content *content, char *str);
int		get_right_error_code(t_content *content);

#endif