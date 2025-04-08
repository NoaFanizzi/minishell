/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:09:58 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/08 17:15:09 by nbodin           ###   ########lyon.fr   */
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

char	**quotes_sep(char **command, char *line);
int		quotes_checker(char *line);
int		forward_till_quote(char *line, size_t *len, char quote);
int		split_quote_count(char *line);
void	fill_quote_words(char **command, char *line, t_index_q *index);



#endif