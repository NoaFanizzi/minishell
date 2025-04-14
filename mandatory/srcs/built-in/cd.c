/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:22:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/11 17:26:57 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_upgrade_pwd(t_list *env)
{
	char	*path;
	char	*temp;
	t_env *cpy;

	path = getcwd(NULL, 0);
	while (env != NULL)
	{
		cpy = (t_env *)env->content;
		if (ft_strncmp(cpy->var, "PWD=", 4) == 0)
		{
			free(cpy->arg);
			temp = ft_strdup("PWD=");
			cpy->arg = ft_strjoin(temp, path);
			free(temp);
			free(path);
			return ;
		}
		env = env->next;
	}
}

void	ft_upgrade_opwd(t_list *env)
{
	char	*path;
	char *temp;
	t_env *cpy;

	path = getcwd(NULL, 0);
	while (env != NULL)
	{
		cpy = (t_env *)env->content;
		if (ft_strncmp(cpy->var, "OLDPWD", 6) == 0)
		{
			free(cpy->arg);
			temp = ft_strdup("OLDPWD=");
			cpy->arg = ft_strjoin(temp, path);
			free(temp);
			free(path);
			return ;
		}
		env = env->next;
	}
}

void	ft_cd(t_list *env, char *cmd)
{
	//size_t	i;

	//i = 0;
	ft_upgrade_opwd(env);
	if (chdir(cmd) == -1)
		write(1, "chdir error", 12);
	ft_upgrade_pwd(env);
}

