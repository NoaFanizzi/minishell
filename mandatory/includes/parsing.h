/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:09:58 by nbodin            #+#    #+#             */
/*   Updated: 2025/05/06 08:53:27 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "minishell.h"

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

#define	D_QUOTE 34
#define S_QUOTE 39

int		main(int argc, char **argv, char **env);
t_content	*launch_shell(char **env);
char	***parse_command(char *line, char **env);
void	analyse_command(char ***cmd_splitted, t_array **array, char **env);

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
int		ft_try(char **env, char *command);

char	***command_splitting(char **command);
char	***init_splitted(char ***splitted, char **command);
char	***fill_splitted_command(char ***splitted, char **command);
int		count_commands(char **command);
int		count_command_words(char **command);

void	create_cmd_struct(char ***cmd_splitted, t_content *content, size_t cmd_index, char **env);
void	identify_cmd_opt(char **cmd, t_content *content, char **env);
size_t	count_cmd_opt(char **cmd, char **env);
void	figure_in_out_files(char **cmd, t_content *content);
size_t	count_redir(char **cmd);
void	identify_arg(char **cmd, t_content *content, char **env);
size_t	count_arg(char **cmd, char **env);


#endif