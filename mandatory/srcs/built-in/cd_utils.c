/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:08:39 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/31 11:51:37 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env(t_list **env, char *var, char *arg)
{
	t_env	*to_replace;

	if(!arg)
		return(0);
	to_replace = get_env(var, *env);
	if (!to_replace)
		return (0);
	free(to_replace->arg);
	to_replace->arg = NULL;
	to_replace->arg = ft_strdup(arg);
	if (!to_replace->arg)
	{
		(void)arg;
		return (1);
	}
	return (0);
}

int	clean_pwd(char *pwd, char *saved_pwd, char *var, t_content *content)
{
	if (pwd)
		free(pwd);
	if (saved_pwd)
		free(saved_pwd);
	pwd = NULL;
	saved_pwd = NULL;
	content->error_code = 1;
	if (!var)
		return (0);
	ft_putstr_fd("maxishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putendl_fd(" not set", STDERR_FILENO);
	return (0);
}

int	update_pwd(t_content *content, t_list **env, char *pwd, char *saved_pwd)
{
	t_env	*node;

	pwd = getcwd(NULL, 0);
	node = get_env("PWD", *env);
	if (update_env(env, "OLDPWD", saved_pwd) == 1)
	{
		free(pwd);
		free(saved_pwd);
		return (ft_open_error(content, NULL));
	}
	if (pwd)
	{
		if (update_env(env, "PWD", pwd) == 1)
		{
			free(pwd);
			free(saved_pwd);
			return (ft_open_error(content, NULL));
		}
	}
	free(saved_pwd);
	content->error_code = 0;
	if (is_not_pwd(content, env, pwd, node) == O_ERROR)
		return (O_ERROR);
	return (1);
}

int	is_not_pwd(t_content *content, t_list **env, char *pwd, t_env *node)
{
	char	*temp;

	if (!pwd)
	{
		node = get_env("PWD", *env);
		temp = ft_strjoin(node->arg, "/");
		if (!temp)
			return (ft_open_error(content, NULL));
		pwd = ft_strjoin(temp, content->arg[0]);
		free(temp);
		if (!pwd)
			return (ft_open_error(content, NULL));
		if (update_env(env, "PWD", NULL) == 1)
		{
			free(pwd);
			return (ft_open_error(content, pwd));
		}
		ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
		ft_putstr_fd("getcwd: cannot access parent dire", STDERR_FILENO);
		ft_putendl_fd("ctories: No such file or directory", STDERR_FILENO);
		content->error_code = 1;
	}
	if (pwd)
		free(pwd);
	return (0);
}
