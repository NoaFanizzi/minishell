#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "structs.h"
#include "exec.h"
#include "parsing.h"
#include "redirections.h"
#include "error_handling.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

extern int g_exit_status;
extern int g_macro_debug;

enum	ERROR
{
	O_ERROR = -10,
	NO_IN = -11,
	NO_OUT = -12
};

//echo.c
int		ft_echo(t_content *content);

//cd.c
void	ft_cd(t_content *content, t_list **env);

//env.c
t_list	*ft_init_env(char **env);
void	ft_display_env(t_list *env);

//pwd.c
int		ft_pwd(void);

//utils.c
void	ft_display_tab(char **tab);
void	ft_free_tab(char **tab);
void	ft_free_content(t_content *content);
void	ft_free_env(t_list *env);


#endif