/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:06:47 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/07 20:01:20 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "exec.h"

# define D_QUOTE 34
# define S_QUOTE 39

// ############ COMMAND ############ //
// command_splitting_utils.c //
void	*free_command(char ***splitted);
int		count_command_words(char **command);
int		count_commands(char **command);

// command_splitting.c //
char	***command_splitting(char **command);
char	***fill_splitted_command(char ***splitted, char **command);
char	***init_splitted(char ***splitted, char **command);
// ################################ //

// ############ CONTIGUOUS ########## //
// contiguous_quotes_helpers.c //
int		call_join_prev(char ***command, char ***cmd, size_t *i, int *merged);
int		call_next_simple(char ***command, char ***cmd, size_t *i, int *merged);
int		call_next_quotes(char ***command, char ***cmd, size_t i, int *merged);
int		call_prev_simple(char ***command, char ***cmd, size_t *i, int *merged);
int		call_prev_quotes(char ***command, char ***cmd, size_t *i, int *merged);

// contiguous_quotes_merging.c //
int		check_if_merge_needed(char ***command, char ***cmd, size_t *i,
			int *merged);
int		should_merge_next(char **command, size_t i);
int		should_merge_prev(char **command, size_t i);
int		are_contiguous(char *prev, char *curr);

// contiguous_quotes_utils.c //
int		ft_isspace(char c);
int		check_free_joined(char ***joined, size_t *k);
void	shift_words(char **command, size_t i);
int		is_quote(char c);
int		is_not_pipe_redir(char c);

// contiguous_quotes.c //
int		contiguous_quotes(char ***cmd);
int		loop_in_continuous(char ***cmd, char ***command, int *changes_made, size_t *i);
int		call_join_next_prev(char ***command, char ***cmd, size_t *i,
			int *merged);
size_t	len_until_space_backward(char *str);
size_t	len_until_space_forward(char *str);
// ##################################//

// ############ EXPAND ############ //
// expand_after.c //
int		is_after_great_var(char *cmd, size_t var_index);
int		is_after_great(char *cmd, size_t var_index);
int		is_not_after_hdoc(char *cmd, size_t var_index);
int		quotes_after(char *cmd, size_t i);

// expand_helpers.c //
void	*look_to_expand(t_expand *data, t_list **env, t_array *array);
int		handle_normal_expand(t_expand *data, t_list **env, t_array *array);
void	*is_not_var(t_expand *data, t_array *array);
int		call_expand_var(t_expand *data, t_list **env, t_array *array);
void	*expand_allocations(t_array *array, char **new_cmd, char **error_code,
			char **command);

// expand_other_utils.c //
int		is_in_single_quotes(const char *cmd, size_t pos);
void	track_quotes_until_meta(int *in_dquote, int *in_squote, char *cmd,
			size_t *i);
char	*get_var_name(char *word);
size_t	get_var_length(char *word);

// expand_quotes.c //
void	switch_back_lit_quotes(char *exp_var);
void	switch_lit_quotes(char *exp_var);
void	*handle_expand_error_code(t_expand *data, t_array *array);
char	*expand_error_code(char *command, size_t i, t_array *array);

// expand_utils.c //
int		copy_error_code(char *new_cmd, size_t *k, char *error_code);
int		track_var_in_del(char *cmd, size_t *i, size_t var_index);
void	skip_redir_spaces(char *cmd, size_t *i);
int		valid_var_char(char c);
int		valid_var_first_char(char c);

// expand.c //
char	*expand_word(char *command, t_list **env, t_array *array);
char	*remove_var(char *command, size_t i);
int		expand_var(t_expand *data, t_list **env, t_array *array);
int		loop_data_in_expand(t_expand *data, t_list **env, t_array *array);
int		expand_var_in_command(t_expand *data, t_list **env, size_t *k);
// ################################ //

// ############ QUOTES ############ //
// join_next_quotes.c //
char	**join_next_quotes(char ***command, size_t i);
int		go_through_join_next_quotes(char **command, char **joined, size_t i);
int		fusion_quotes_next(char **command, char **joined, size_t i, size_t j);
int		handle_space_case(char **command, char **joined, size_t *sk, size_t j);

// join_next_simple.c //
char	**join_next_simple(char ***command, size_t i);
int		go_through_join_next_simple(char **command, char **joined, size_t i);
int		manage_next_simple(char **command, char ***joined, size_t idx[3]);
int		fusion_simple_next(char **command, char **joined, size_t idx[3]);
int		alloc_and_prepare_joined(char **command, char **joined, size_t idx[3]);

// join_prev_quotes.c //
char	**join_prev_quotes(char ***command, size_t i);
void	go_through_join_prev_quotes(char **command, char **joined, size_t i);
void	fusion_quotes_prev(char **command, char **joined, size_t i, size_t j);

// join_prev_simple.c //
char	**join_prev_simple(char ***command, size_t i);
int		go_through_join_prev_simple(char **command, char **joined, size_t i);
int		handle_prev_join_special(char **command, char **joined, size_t i,
			size_t jk[2]);
int		fusion_simple_prev(char **command, char **joined, size_t i, size_t j);
int		create_final_string(char **command, char **joined, size_t *sk,
			size_t ij[2]);

// quotes_removal.c //
void	quotes_removal(char **command);
void	rem_and_shift(char *command);

// quotes_splitting_utils.c //
int		quotes_checker(char *line);
void	skip_inside_quotes(size_t *i, size_t *j, char *line, int *count);
int		forward_till_quote(char *line, size_t *len, char quote);

// quotes_splitting.c //
char	**quotes_splitting(char **command, char *line);
char	**fill_quote_words(char **command, char *line, size_t k, size_t *i);
void	*return_malloc_error(void);
int		split_quote_count(char *line);
// ################################ //

// ############ SYNTAX ############ //
// analyse_command.c //
int		process_command(char *line, t_list **var, t_array *array,
			char ****cmd_splitted);
int		analyse_command(char ***cmd_splitted, t_array *array);
int		create_structs_loop(char ***cmd_splitted, t_array *array,
			size_t *cmd_index, size_t *struct_index);
void	fill_struct_size(t_array *array, size_t struct_index);
void	get_array_size(char ***cmd_splitted, t_array *array);

// charset_split.c //
char	**fill_splitted(const char *s, const char *charset, char **splitted,
			size_t *j);
void	*free_words(char **splitted);
int		count_words(const char *str, const char *charset);
int		is_sep(char c, const char *charset);

// check_syntax_utils.c //
int		check_pipe_end(char *cmd);
int		check_op_count(int op_count, char op);
int		check_new_redir_seq(char *cmd, size_t *i, int spaced_after, char op);
void	skip_spaces(char *cmd, size_t *i, int *spaced_after);
void	handle_quote_state(int *in_dquote, int *in_squote, char *cmd,
			size_t *i);

// check_syntax.c //
int		check_syntax(char *cmd);
int		check_redir_pipes(char *cmd);
int		check_consecutive_pipes(char *cmd, size_t *i);
int		check_pipe_start(char *cmd);
int		check_redir(char *cmd, size_t *i);

// cmd_struct_utils.c //
size_t	count_redir(char **cmd);
size_t	skip_opt_and_redirs(char **cmd, size_t start);
int		is_var_assign(char *str);
char	*find_command_name(char **cmd, size_t *i);

// cmd_struct.c //
int		create_cmd_struct(char ***cmd_splitted, t_content *content,
			size_t cmd_index, t_array *array);
int		free_arg(t_content *content, t_array *array);
int		free_cmd_opt(t_content *content, t_array *array);
int		free_in_out_files(t_content *content, t_array *array);
int		figure_in_out_files(char **cmd, t_content *content);

// figure_arg.c //
int		identify_arg(char **cmd, t_content *content);
int		fill_args(char **cmd, size_t start, char **arg);
size_t	count_arg(char **cmd);
size_t	count_real_args(char **cmd, size_t start);

// figure_cmd_opt.c //
int		identify_cmd_opt(char **cmd, t_content *content);
int		assign_cmd_and_opt(char **cmd, t_content *content);
int		copy_opt(t_content *content, char **cmd, size_t *j, size_t i);
size_t	count_cmd_opt(char **cmd);

// figure_files.c //
int		check_for_op(char **cmd, t_content *content, int tab[2],
			size_t redir_count);
void	figure_out(char **cmd, t_content *content, int tab[2],
			size_t redir_count);
void	figure_in(char **cmd, t_content *content, int tab[2],
			size_t redir_count);
void	figure_append(char **cmd, t_content *content, int tab[2],
			size_t redir_count);
int		figure_hdoc(char **cmd, t_content *content, int tab[2],
			size_t redir_count);

// hdoc.c //
int		create_hdoc_struct(char **command, t_content *content, t_array *array);
void	fill_hdocs(char **command, t_heredocs *hdoc, size_t hdoc_count);
int		count_hdoc_nb(char **command);

// meta_splitting_utils.c //
int		add_segment(const char *s, char ***splitted, size_t *j, int tab[2]);
int		twisted_count_words(char *str, const char *charset);

// meta_splitting.c //
char	**meta_splitting(char **command);
char	**fill_meta_words(char **splitted, char **command, const char *charset);
char	**twisted_fill_splitted(const char *s, const char *charset,
			char **splitted, size_t *j);
size_t	find_next_segment(const char *s, const char *charset, size_t start);
int		split_meta_count(char **command, const char *charset);

// parse_command.c //
char	***parse_command(char **line, t_list **var, t_array *array);
char	*prepare_line(char **line, t_list **var, t_array *array);
char	***parse_splitting_part(char ***command, t_array *array);

// space_splitting.c //
char	**space_splitting(char **command);
char	**fill_space_words(char **splitted, char **command,
			const char *charset);
int		split_space_count(char **command, const char *charset);

// utils.c //
void	ft_free_content(t_content *content);
void	ft_free_array_content(t_array *array);
void	ft_close_array_fd(t_content *content, size_t pos);
void	ft_free_files(t_content *content);
void	ft_free_env(t_list *env);
// ################################ //

// launch_shell.c //
int		launch_shell(t_list **var, t_array *array);
int		call_check_syntax(char *line, char *temp_line, t_array *array);
void	*manage_readline(char **line, t_array *array, t_list **var);
char	*ft_join_prompt(t_array *array);

#endif