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
#include <sys/stat.h>
#include <sys/select.h>

enum debug
{
	REDIR = 1,
	ALL = 3,
};

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

typedef struct s_expar
{
	int		fd;
	int		size;
	pid_t	pid_1;
	pid_t	pid_2;
	char	*path;
	char	**options;
}			t_expar;

typedef struct s_content
{
	char **cmd;
	char **arg; 
	char ***cmd_splitted;
	t_files *files;
	t_heredocs	*hdoc;
	pid_t pid;
	int	infile;
	int	outfile;
	int	size;
	int pos;
	int redir_count;
	int error_code;
	int h_fd;
	int	stdin_saved;
	int stdout_saved;
	struct s_array *array_ptr;
	t_expar *expar;
	t_list **env;
	int fd_array[FD_SETSIZE];

}			t_content;


typedef struct s_array
{
	t_content *content;
	int		(*pipe)[2];
	int size;
	int p_exit_status;
	int hdoc_length;
	int is_lost;
}				t_array;

typedef struct s_expand
{
	char	*new_command;
	size_t	i;
	size_t	new_length;
	char 	*var_name;
}				t_expand;

#endif

