/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:22:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/26 14:42:46 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_upgrade_pwd(t_env *env)
{
	size_t	i;
	char	*path;
	char	*temp;

	i = 0;
	path = getcwd(NULL, 0);
	while (env->var[i])
	{
		if (ft_strncmp(env->var[i], "PWD=", 4) == 0)
		{
			free(env->var[i]);
			temp = ft_strdup("PWD=");
			env->var[i] = ft_strjoin(temp, path);
			free(temp);
			free(path);
			return ;
		}
		i++;
	}
}

void	ft_upgrade_opwd(t_env *env)
{
	size_t	i;
	char	*path;
	char *temp;

	i = 0;
	path = getcwd(NULL, 0);
	while (env->var[i])
	{
		if (ft_strncmp(env->var[i], "OLDPWD=", 7) == 0)
		{
			free(env->var[i]);
			temp = ft_strdup("OLDPWD=");
			env->var[i] = ft_strjoin(temp, path);
			free(temp);
			free(path);
			return ;
		}
		i++;
	}
}

void	ft_cd(t_env *env, char *cmd)
{
	size_t	i;

	i = 0;
	ft_upgrade_opwd(env);
	if (chdir(cmd) == -1)
		write(1, "chdir error", 12);
	ft_upgrade_pwd(env);
}

