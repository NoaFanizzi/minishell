#ifndef STRUCTS_H
#define STRUCTS_H

# include "libft.h"
# include "minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_export
{
	char *var;
	int	value;
	int status; //set a 0 si y'a pas de value et set a 1 des que y'a une value
}				t_export;

/* typedef struct s_env
{
	char *var;
	char *op;
	char *arg;
	int	exp;
	struct s_env *next;
}				t_env;
 */

typedef struct s_env
{
	char *var;
	char *op;
	char *arg;
	int	exp;
}				t_env;

// typedef struct s_var
// {
// 	t_env *env;
// 	t_export *export;
// 	int export_size;
// }				t_var;

typedef enum redir
{
	IN,
	OUT,
	APND, //append
	PIPE, //pipe
	HDOC // sortie d'erreur
}			t_redir;


typedef struct s_files
{
	int	index;
	enum redir type;
}				t_files;

typedef struct s_content //TODO toujours malloc cmd a minimum 4 parce que j'ai 4 trucs a envoyer et ca evite d'avoir a faire des reallocations
{
	char **cmd;// Peut-etre faire un tableau de tableau pour cmd + options parce que moi je dois donner un tableau de tableau a execve
	char *arg; //TODO TEJ le arg et tout mettre dans cmd
	t_files *files;
	pid_t pid;
	int	infile;
	int	outfile;
	int	size;
}			t_content;

typedef struct s_array
{
	t_content *content;
	int size;
}				t_array;

typedef struct s_expar
{
	int		pipe[2];
	int		fd;
	pid_t	pid_1;
	pid_t	pid_2;
	char	*path;
	char	**options;
}			t_expar;



#endif