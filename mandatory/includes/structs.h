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

typedef struct s_env
{
	char *var;
	char *op;
	char *arg;
	int	exp;
}				t_env;


enum redir
{
	STDIN,
	STDOUT,
    IN,
    OUT,
    APND,
    HDOC,
	PIPE,
};

typedef struct s_files
{
	int	index;
	size_t	size;
	enum redir type;
	char	*eof;
}				t_files;

typedef struct s_heredocs
{
	char	**text;
	int		s_quoted;
	size_t	size;
}				t_heredocs;

typedef struct s_content //TODO toujours malloc cmd a minimum 4 parce que j'ai 4 trucs a envoyer et ca evite d'avoir a faire des reallocations
{
	char **cmd;// Peut-etre faire un tableau de tableau pour cmd + options parce que moi je dois donner un tableau de tableau a execve
	char **arg; //TODO TEJ le arg et tout mettre dans cmd
	char ***cmd_splitted;
	t_files *files;
	t_heredocs	*hdoc;
	pid_t pid;
	int	infile;
	int	outfile;
	int	size;
	int pos;
	struct s_array *array_ptr;
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

//TO DO y'a plus de pipes, je check par rapport a la ou j'en suis dans mon nombre de commande pour savoir si c'est un pipe
//TODO modifier la fonction qui check si y'a des pipes et l'ordre d'ouverture
//TODO bien se rappeler qu'on se repere par rapport au maillon de l'array de content. ENtre chaque mailon y'a un pipe. Donc tej le pipe dans le .h aussi
#endif