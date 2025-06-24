/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:09:58 by nbodin            #+#    #+#             */
/*   Updated: 2025/06/24 11:20:21 by nbodin           ###   ########lyon.fr   */
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

int		main(int argc, char **argv, char **env);
void	launch_shell(t_list **var);
char	***parse_command(char *line);
void	analyse_command(char ***cmd_splitted, t_array *array, t_list *var);
void    fill_struct_size(t_array *array, size_t struct_index);
int	    create_hdoc_struct(t_array *array, char **command);

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

int		ft_check_if_command(char *cmd, char **path);
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
void	figure_in_out_files(char **cmd, t_content *content);
size_t	count_redir(char **cmd);
void	identify_arg(char **cmd, t_content *content);
size_t	count_arg(char **cmd);
char	*find_command_name(char **cmd, size_t *i);
int		is_var_assign(char *str);



int		ft_isspace(char c);
void	fusion_quotes_next(char **command, char **joined, size_t i, size_t j);
void	go_through_join_next_quotes(char **command, char **joined, size_t i);
char	**join_next_quotes(char **command, size_t i);
void	fusion_simple_next(char **command, char **joined, size_t i, size_t j);
void	go_through_join_next_simple(char **command, char **joined, size_t i);
char	**join_next_simple(char **command, size_t i);
void	fusion_simple_prev(char **command, char **joined, size_t i, size_t j);
void	go_through_join_prev_simple(char **command, char **joined, size_t i);
char	**join_prev_simple(char **command, size_t i);
void	fusion_quotes_prev(char **command, char **joined, size_t i, size_t j);
void	go_through_join_prev_quotes(char **command, char **joined, size_t i);
char	**join_prev_quotes(char **command, size_t i);
void	contiguous_quotes(char ***command);



#endif