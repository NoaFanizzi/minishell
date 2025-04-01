#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "exec.h"
#include <unistd.h>
#include <stdio.h>


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
	pid_t pid;


}			t_content;

typedef struct s_array
{
	t_content *content;
	int size;
}				t_array;

//echo.c
int		ft_echo(char **cmd);

//cd.c
void	ft_cd(t_env *env, char *cmd);

//env.c
void	ft_init_env(char **env, t_env *cpy);
void	ft_display_env(char **tab);

//pwd.c
void	ft_pwd(void);

//utils.c
void	ft_display_tab(char **tab);
void	ft_free_tab(char **tab);


#endif