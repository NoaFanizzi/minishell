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
void	ft_cd(t_env *env, char *cmd);

//env.c
void	ft_init_env(char **env, t_env *cpy);
void	ft_display_env(char **tab);

//pwd.c
void	ft_pwd(void);

//utils.c
void	ft_display_tab(char **tab);
void	ft_free_tab(char **tab);
void	ft_free_content(t_content *content);


#endif