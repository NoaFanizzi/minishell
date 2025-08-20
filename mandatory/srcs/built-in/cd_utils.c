/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:08:39 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/20 12:43:05 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env(t_list **env, char *var, char *arg)
{
	t_env	*to_replace;

	if (!arg)
		return (0);
	to_replace = get_env(var, *env);
	if (!to_replace)
		return (0);
	free(to_replace->arg);
	to_replace->arg = NULL;
	to_replace->arg = ft_strdup(arg); // PROTECTED
	if (!to_replace->arg)
	{
		(void)*arg;
		return (1);
	}
	return (0);
}

int	clean_pwd(char **pwd, char **saved_pwd, char *var, t_content *content)
{
	if (*pwd)
		ft_wipe(pwd);
	if (*saved_pwd)
		ft_wipe(saved_pwd);
	content->error_code = 1;
	if (!var)
		return (0);
	if (var)
	{
		ft_putstr_fd("maxishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(var, STDERR_FILENO);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (0);
}

int	update_pwd(t_content *content, t_list **env, char **pwd, char **saved_pwd)
{
	t_env	*node;

	*pwd = getcwd(NULL, 0); //PROTECTED
	node = get_env("PWD", *env);
	if (update_env(env, "OLDPWD", *saved_pwd) == 1)
	{
		ft_wipe(pwd);
		ft_wipe(saved_pwd);
		return (ft_open_error(content, NULL));
	}
	if (*pwd)
	{
		if (update_env(env, "PWD", *pwd) == 1)
		{
			ft_wipe(pwd);
			ft_wipe(saved_pwd);
			return (ft_open_error(content, NULL));
		}
	}
	ft_wipe(saved_pwd);
	if (is_not_pwd(content, env, pwd, node) == O_ERROR)
		return (O_ERROR);
	return (1);
}

int	get_final_pwd(t_content *content, t_list **env, char **pwd, t_env *node)
{
	char	*temp;

	node = get_env("PWD", *env);
	if (!node || !node->arg)
	{
		content->error_code = 1;
		return (0);
	}
	temp = ft_strjoin(node->arg, "/"); // PROTECTED
	if (!temp)
		return (ft_open_error(content, NULL));
	if (content->arg)
		*pwd = ft_strjoin(temp, content->arg[0]); // PROTECTED
	else
		*pwd = ft_strdup(temp); //PROTECTED
	ft_wipe(&temp);
	if (!*pwd)
		return (ft_open_error(content, NULL));
	return (2);
}

int	is_not_pwd(t_content *content, t_list **env, char **pwd, t_env *node)
{
	int	returned_value;

	if (!*pwd)
	{
		returned_value = get_final_pwd(content, env, pwd, node);
		if (returned_value != 2)
			return (returned_value);
		if (update_env(env, "PWD", NULL) == 1)
		{
			ft_wipe(pwd);
			return (ft_open_error(content, NULL));
		}
		ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
		ft_putstr_fd("getcwd: cannot access parent dire", STDERR_FILENO);
		ft_putendl_fd("ctories: No such file or directory", STDERR_FILENO);
		content->error_code = 1;
	}
	content->error_code = 0;
	if (*pwd)
		ft_wipe(pwd);
	return (0);
}
