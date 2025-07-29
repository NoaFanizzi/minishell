/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:09:58 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 13:37:15 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "libft.h"
#include "minishell.h"
#include "exec.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

#define	D_QUOTE 34
#define S_QUOTE 39


void	print_cmd_splitted(char ***cmd_splitted);
void	print_cmd(char **cmd);



char	***parse_splitting_part(char ***command);
char	***parse_command(char **line, t_list **var, t_array *array);

int	call_prev_quotes(char ***command, char ***cmd, size_t *i, int *merged);
int	call_prev_simple(char ***command, char ***cmd, size_t *i, int *merged);
int	call_next_quotes(char ***command, char ***cmd, size_t i, int *merged);
int	call_next_simple(char ***command, char ***cmd, size_t *i, int *merged);
int	call_join_prev(char ***command, char ***cmd, size_t *i, int *merged);

int	is_not_pipe_redir(char c);
int	is_quote(char c);
void	shift_words(char **command, size_t i);
int	check_free_joined(char ***joined, size_t *k);
int	ft_isspace(char c);

void	fusion_quotes_next(char **command, char **joined, size_t i, size_t j);
void	go_through_join_next_quotes(char **command, char **joined, size_t i);
char	**join_next_quotes(char ***command, size_t i);

void	fusion_simple_next(char **command, char **joined, size_t i, size_t j);
void	go_through_join_next_simple(char **command, char **joined, size_t i);
char	**join_next_simple(char ***command, size_t i);

void	fusion_quotes_prev(char **command, char **joined, size_t i, size_t j);
void	go_through_join_prev_quotes(char **command, char **joined, size_t i);
char	**join_prev_quotes(char ***command, size_t i);

void	fusion_simple_prev(char **command, char **joined, size_t i, size_t j);
void	go_through_join_prev_simple(char **command, char **joined, size_t i);
char	**join_prev_simple(char ***command, size_t i);

void	contiguous_quotes(char ***cmd);
int	call_join_next_prev(char ***command, char ***cmd, size_t *i, int *merged);
size_t	len_until_space_backward(char *str);
size_t	len_until_space_forward(char *str);

size_t	count_redir(char **cmd);
size_t	skip_opt_and_redirs(char **cmd, size_t start);
int	is_var_assign(char *str);
char	*find_command_name(char **cmd, size_t *i);

void	create_cmd_struct(char ***cmd_splitted, t_content *content,
		size_t cmd_index);
void	figure_in_out_files(char **cmd, t_content *content);

void	fill_args(char **cmd, size_t start, char **arg);
void	identify_arg(char **cmd, t_content *content);
size_t	count_arg(char **cmd);
size_t	count_real_args(char **cmd, size_t start);

void	identify_cmd_opt(char **cmd, t_content *content);
void	assign_cmd_and_opt(char **cmd, t_content *content);
size_t	count_cmd_opt(char **cmd);

void	check_for_op(char **cmd, t_content *content, int tab[2],
		size_t redir_count);
void	figure_out(char **cmd, t_content *content, int tab[2],
		size_t redir_count);
void	figure_append(char **cmd, t_content *content, int tab[2],
		size_t redir_count);
void	figure_hdoc(char **cmd, t_content *content, int tab[2],
		size_t redir_count);

char	**add_segment(const char *s, char **splitted, size_t *j, int tab[2]);
int	twisted_count_words(char *str, const char *charset);

void	analyse_command(char ***cmd_splitted, t_array *array);
void	fill_struct_size(t_array *array, size_t struct_index);
void	get_array_size(char ***cmd_splitted, t_array *array);

int	create_hdoc_struct(char **command, t_content *content);
void	fill_hdocs(char **command, t_heredocs *hdoc, size_t hdoc_count);
int	count_hdocnb(char **command);

void	*free_command(char ***splitted);
int	count_command_words(char **command);
int	count_commands(char **command);

int	forward_till_quote(char *line, size_t *len, char quote);
void	skip_inside_quotes(size_t *i, size_t *j, char *line, int *count);
int	quotes_checker(char *line);

char	*expand_word(char *command, t_list **env, t_array *array);
char	*remove_var(char *command, size_t i);
char	*expand_var(t_expand *data, t_list **env);
void	expand_var_in_command(t_expand *data, t_list **env, size_t *k,
		char *new_word);

int	copy_error_code(char *new_cmd, size_t *k, char *command,
		char *error_code);
int	track_var_in_del(char *cmd, size_t *i, size_t var_index);
void	skip_redir_spaces(char *cmd, size_t *i);
int	valid_var_char(char c);
int	valid_var_first_char(char c);

int	is_in_single_quotes(const char *cmd, size_t pos);
void	track_quotes_until_meta(int *in_dquote, int *in_squote, char *cmd,
		size_t *i);
char	*get_var_name(char *word);
size_t	get_var_length(char *word);

void	*look_to_expand(t_expand *data, t_list **env, t_array *array);
void	*handle_normal_expand(t_expand *data, t_list **env);
void	*call_expand_var(t_expand *data, t_list **env);
void	*handle_expand_error_code(t_expand *data, t_array *array);
char	*expand_error_code(char *command, size_t i, t_array *array);

int	is_after_great_var(char *cmd, size_t var_index);
int	is_after_great(char *cmd, size_t var_index);
int	is_not_after_hdoc(char *cmd, size_t var_index);
int	quotes_after(char *cmd, size_t i);




int		check_syntax(char *cmd);
int 	check_pipe_end(char *cmd);
int		check_pipe_start(char *cmd);
int		check_redir_pipes(char *cmd);
int		check_redir(char *cmd, size_t *i);
int		check_op_count(int op_count, char op);
int		check_consecutive_pipes(char *cmd, size_t *i);
int		check_new_redir_seq(char *cmd, size_t *i, int spaced_after, char op);
void	skip_spaces(char *cmd, size_t *i, int *spaced_after);
void	handle_quote_state(int *in_dquote, int *in_squote, char *cmd, size_t *i);

int		main(int argc, char **argv, char **env);
int	launch_shell(t_list **var, t_array *array);
char	***parse_command(char **line, t_list **var, t_array *array);
void	analyse_command(char ***cmd_splitted, t_array *array);
void    fill_struct_size(t_array *array, size_t struct_index);
int    create_hdoc_struct(char **command, t_content *content);

char	**quotes_splitting(char **command, char *line);
int		quotes_checker(char *line);
int		forward_till_quote(char *line, size_t *len, char quote);
int		split_quote_count(char *line);
char	**fill_quote_words(char **command, char *line, size_t k, size_t *i);

char	**space_splitting(char **command);
char	**fill_space_words(char **command, char **splitted, const char *charset);
int		split_space_count(char **command, const char *charset);

char	**fill_splitted(const char *s, const char *charset, char **splitted, size_t *j);
void	*free_words(char **splitted);
int		count_words(const char *str, const char *charset);
int		is_sep(char c, const char *charset);

char	**meta_splitting(char **command);
int		split_meta_count(char **command, const char *charset);
int		twisted_count_words(char *str, const char *charset);
char	**fill_meta_words(char **splitted, char **command, const char *charset);
char	**twisted_fill_splitted(const char *s, const char *charset, char **splitted, size_t *j);


void	quotes_removal(char **command);
void	rem_and_shift(char *command);

int 	ft_is_command_parsing(t_expar *expar, char *command);
int		ft_try(t_list *var, char *command);

char	***command_splitting(char **command);
char	***init_splitted(char ***splitted, char **command);
char	***fill_splitted_command(char ***splitted, char **command);
int		count_commands(char **command);
int		count_command_words(char **command);
void	*free_command(char ***splitted);

void	create_cmd_struct(char ***cmd_splitted, t_content *content, size_t cmd_index);
void	identify_cmd_opt(char **cmd, t_content *content);
size_t	count_cmd_opt(char **cmd);
void	create_cmd_struct(char ***cmd_splitted, t_content *content, size_t cmd_index);
void	identify_cmd_opt(char **cmd, t_content *content);
size_t	count_cmd_opt(char **cmd);
void	figure_in_out_files(char **cmd, t_content *content);
size_t	count_redir(char **cmd);
void	identify_arg(char **cmd, t_content *content);
size_t	count_arg(char **cmd);
char	*find_command_name(char **cmd, size_t *i);
int		is_var_assign(char *str);

int	check_syntax(char *cmd);

char	*expand_word(char *command, t_list **env, t_array *array);

#endif