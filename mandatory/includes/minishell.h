#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "structs.h"
#include "exec.h"
#include <unistd.h>
#include <stdio.h>

//echo.c
int		ft_echo(t_content *content, t_expar *expar);

//cd.c
void	ft_cd(t_list *var, char *cmd);

//env.c
t_list	*ft_init_env(char **env);
void	ft_display_env(t_list *env);

//pwd.c
void	ft_pwd(void);

//utils.c
void	ft_display_tab(char **tab);
void	ft_free_tab(char **tab);
void	ft_free_content(t_content *content);
void	ft_free_env(t_list *env);


#endif