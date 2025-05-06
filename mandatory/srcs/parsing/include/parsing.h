/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:09:58 by nbodin            #+#    #+#             */
/*   Updated: 2025/05/06 09:58:41 by nbodin           ###   ########lyon.fr   */
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

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

#define	D_QUOTE 34
#define S_QUOTE 39

typedef struct s_export
{
	char 	*var;
	int		value;
	int 	status; //set a 0 si y'a pas de value et set a 1 des que y'a une value
}				t_export;

/* typedef struct s_env
{
char *var;
char *op;
char *arg;
intexp;
struct s_env *next;
}t_env;
 */

typedef struct s_env
{
	char 	*var;
	char 	*op;
	char 	*arg;
	int		exp;
}				t_env;

// typedef struct s_var
// {
// t_env *env;
// t_export *export;
// int export_size;
// }t_var;

enum redir
{
    IN,
    OUT,
    APND, //append
    HDOC // sortie d'erreur
};


typedef struct s_files
{
    int    		index;
    enum redir type;
}                t_files;

typedef struct s_content //TODO toujours malloc cmd a minimum 4 parce que j'ai 4 trucs a envoyer et ca evite d'avoir a faire des reallocations
{
    char 	**cmd;// Peut-etre faire un tableau de tableau pour cmd + options parce que moi je dois donner un tableau de tableau a execve
    char	**arg; //TODO TEJ le arg et tout mettre dans cmd
    t_files *files;
    pid_t 	pid;
}            t_content;

typedef struct s_array
{
	t_content 	*content;
	int 		size;
}				t_array;

typedef struct s_expar
{
	int		pipe[2];
	int		fd;
	pid_t	pid_1;
	pid_t	pid_2;
	char	*path;
	char	**options;
}				t_expar;


int		main(int argc, char **argv, char **env);
t_content	*launch_shell(char **env);
char	***parse_command(char *line);
void	analyse_command(char ***cmd_splitted, t_array **array, t_list *var);

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
int 	ft_is_command(t_expar *expar, char *command);
int		ft_try(t_list *var, char *command);
t_list	*ft_init_env(char **env);
char	**ct_get_paths(t_list *var);
t_env	*ft_add_new_link(char *env);
void    ft_free_env(t_list *env);

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