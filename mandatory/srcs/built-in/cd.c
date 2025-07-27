/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:22:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/28 00:53:43 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_list **env, char *var, char *arg)
{
	t_env *to_replace;
	
	to_replace = get_env(var, *env);
	if(!to_replace)
		return;
	free(to_replace->arg);
	to_replace->arg = ft_strdup(arg);
}

int	clean_pwd(char *pwd, char *saved_pwd, char *var, t_content *content)
{
	if(pwd)
		free(pwd);
	if(saved_pwd)
		free(saved_pwd);
	content->error_code = 1;
	if(!var)
		return(0);
	ft_putstr_fd("maxishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putendl_fd(" not set", STDERR_FILENO);
	return(0);
}

int	update_pwd(t_content *content, t_list **env, char *pwd, char *saved_pwd)
{
	t_env *node;
	char *temp;
	
	pwd = getcwd(NULL, 0);
	node = get_env("PWD", *env);
	update_env(env,"OLDPWD", saved_pwd);
	if(pwd)
		update_env(env,"PWD", pwd);
	free(saved_pwd);
	content->error_code = 0;
	if(!pwd)
	{
		node = get_env("PWD", *env);
		temp = ft_strjoin(node->arg, "/");
		pwd = ft_strjoin(temp, content->arg[0]);
		free(temp);
		update_env(env, "PWD", pwd);
		ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
		ft_putendl_fd("getcwd: cannot access parent directories: No such file or directory", STDERR_FILENO);
		content->error_code = 1;
	}
	if(pwd)
		free(pwd);
	return(1);
}

int	is_dash(t_content *content, char **dir, char **pwd, char **saved_pwd)
{
	t_env *node;

	(void)saved_pwd;
	(void)pwd;
	if(content->cmd[1] && ft_strcmp(content->cmd[1], "-") == 0)
	{
		node = get_env("OLDPWD", *(content->env));
		if(node)
			*dir = ft_strdup(node->arg);
		else
			*dir = NULL;
		node = get_env("PWD", *(content->env));
		if(node == NULL)
			*saved_pwd = NULL;
		else
			*saved_pwd = ft_strdup(node->arg);
		node = get_env("HOME", *(content->env));
		if(node == NULL)
		{
			clean_pwd(*pwd, *saved_pwd, "HOME", content);
			return(0);
		}
		return(1);
	}
	return(0);
}

int	is_arg(t_content *content, char **dir, char **pwd, char **saved_pwd)
{
	char *temp;
	t_env *node;
	
	(void)pwd;
	*saved_pwd = getcwd(NULL, 0);
	if(*saved_pwd)
	{
		temp = ft_strjoin(*saved_pwd, "/");
		*dir = ft_strjoin(temp, content->arg[0]);
		free(temp);
	}
	else
	{
		node = get_env("PWD", *(content->env));
		if(node == NULL)
			*saved_pwd = NULL;
		else
			*saved_pwd = ft_strdup(node->arg);
		*dir = ft_strdup(content->arg[0]);
	}
	return(1);
}

int load_dir(t_content *content, char **dir, char **pwd, char **saved_pwd)
{
	t_env *node;
	
	*pwd = NULL;
	*dir = NULL;
	
	if(content->arg)
		return(is_arg(content, dir, pwd, saved_pwd));
	if(!content->arg)
	{
		if(is_dash(content, dir, pwd, saved_pwd) == 1)
			return(1);
		node = get_env("PWD", *(content->env));
		if(node == NULL)
			*saved_pwd = NULL;
		else
			*saved_pwd = ft_strdup(node->arg);
		node = get_env("HOME", *(content->env));
		if(node == NULL)
		{
			clean_pwd(*pwd, *saved_pwd, "HOME", content);
			return(0);
		}
		*dir = ft_strdup(node->arg);
	}
	return(1);
}

void	ft_cd(t_content *content, t_list **env)
{
	char *pwd;
	char *saved_pwd;
	char *dir;
	
	if(ft_tablen(content->cmd) != 1 && ft_strcmp(content->cmd[1], "-") != 0)
	{
		ft_putendl_fd("maxishell: cd: too many arguments", STDERR_FILENO);
		return;
	}
	if(load_dir(content, &dir, &pwd, &saved_pwd) == 0)
		return;
	if(access(dir, X_OK) == -1)
	{
		ft_putstr_fd("maxishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(content->arg[0], STDERR_FILENO);
		content->error_code = 1;
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
		clean_pwd(pwd, saved_pwd, NULL, content);
		free(dir);
		
		return;
	}
	if(chdir(dir) == -1)
	{
		ft_putstr_fd("maxishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(content->arg[0], STDERR_FILENO);
		ft_putendl_fd(": no such file or directory", STDERR_FILENO);
		content->error_code = 1;
	}
	free(dir);
	update_pwd(content, env, pwd, saved_pwd);
}
