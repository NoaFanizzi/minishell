/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:09:58 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/12 16:32:06 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "get_next_line_1/get_next_line.h"
#include "../../../../libft/includes/libft.h" 

#define	D_QUOTE 34
#define S_QUOTE 39

typedef struct s_content
{
	char **cmd;// Peut-etre faire un tableau de tableau pour cmd + options parce que moi je dois donner un tableau de tableau a execve
	char *arg;
	int input; // int ou char ? Est ce que j'open dans l'exec ou on open dans le parsing ?
	int output; //pareil pour l'output
	int	pipe;
	int overwrite;
	pid_t pid;


}			t_content;

typedef struct s_index_q
{
	size_t	i;
	size_t	j;
	size_t	k;
}				t_index_q;


typedef struct s_array
{
	t_content *content;
	int size;
}				t_array;

int		main(void);
void	launch_shell(void);
void	parse_command(char *line);

char	**quotes_splitting(char **command, char *line);
int		quotes_checker(char *line);
int		forward_till_quote(char *line, size_t *len, char quote);
int		split_quote_count(char *line);
char	**fill_quote_words(char **command, char *line, size_t k, size_t *i);

char	**space_splitting(char **command);
char	**fill_space_words(char **command, char **splitted, const char *charset);
int		split_space_count(char **command, const char *charset);

char	**fill_splitted(const char *s, const char *charset, char **splitted, size_t *j);
void	*free_words(char **splitted, size_t j);
int		count_words(const char *str, const char *charset);
int		is_sep(char c, const char *charset);

char	**meta_splitting(char **command);
int		split_meta_count(char **command, const char *charset);
int		twisted_count_words(char *str, const char *charset);
char	**fill_meta_words(char **splitted, char **command, const char *charset);
char	**twisted_fill_splitted(const char *s, const char *charset, char **splitted, size_t *j);


#endif