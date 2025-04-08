/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:22:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/08 12:29:24 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_upgrade_pwd(t_var *var)
{
	size_t	i;
	char	*path;
	char	*temp;

	i = 0;
	path = getcwd(NULL, 0);
	while (var->env[i])
	{
		if (ft_strncmp(var->env[i], "PWD=", 4) == 0)
		{
			free(var->env[i]);
			temp = ft_strdup("PWD=");
			var->env[i] = ft_strjoin(temp, path);
			free(temp);
			free(path);
			return ;
		}
		i++;
	}
}

void	ft_upgrade_opwd(t_var *var)
{
	size_t	i;
	char	*path;
	char *temp;

	i = 0;
	path = getcwd(NULL, 0);
	while (var->env[i])
	{
		if (ft_strncmp(var->env[i], "OLDPWD=", 7) == 0)
		{
			free(var->env[i]);
			temp = ft_strdup("OLDPWD=");
			var->env[i] = ft_strjoin(temp, path);
			free(temp);
			free(path);
			return ;
		}
		i++;
	}
}

void	ft_cd(t_var *var, char *cmd)
{
	size_t	i;

	i = 0;
	ft_upgrade_opwd(var);
	if (chdir(cmd) == -1)
		write(1, "chdir error", 12);
	ft_upgrade_pwd(var);
}

