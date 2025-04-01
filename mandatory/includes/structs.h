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

typedef struct s_env
{
	char **var;
}				t_env;

typedef struct s_content
{
	char **cmd;// Peut-etre faire un tableau de tableau pour cmd + options parce que moi je dois donner un tableau de tableau a execve
	char *arg;
	int input; // int ou char ? Est ce que j'open dans l'exec ou on open dans le parsing ?
	int output; //pareil pour l'output
	int overwrite;
	int pipe;
	pid_t pid;
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