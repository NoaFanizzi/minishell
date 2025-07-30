/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:22:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/30 14:32:21 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_saved_pwd(t_content *content, char **dir, char **saved_pwd)
{
	char	*temp;

	temp = ft_strjoin(*saved_pwd, "/");
	if (!temp)
	{
		free(*saved_pwd);
		return (ft_open_error(content, NULL));
	}
	*dir = ft_strjoin(temp, content->arg[0]);
	free(temp);
	if (!*dir)
	{
		free(*saved_pwd);
		return (ft_open_error(content, NULL));
	}
	return (1);
}

int	is_arg(t_content *content, char **dir, char **saved_pwd)
{
	t_env	*node;

	*saved_pwd = getcwd(NULL, 0);
	if (*saved_pwd)
		return (is_a_saved_pwd(content, dir, saved_pwd));
	else
	{
		node = get_env("PWD", *(content->env));
		if (node == NULL)
			*saved_pwd = NULL;
		else
		{
			*saved_pwd = ft_strdup(node->arg);
			if (!*saved_pwd)
				return (ft_open_error(content, NULL));
		}
		*dir = ft_strdup(content->arg[0]);
		if (!*dir)
		{
			free(*saved_pwd);
			return (ft_open_error(content, NULL));
		}
	}
	return (1);
}

int	load_dir(t_content *content, char **dir, char **pwd, char **saved_pwd)
{
	int		return_value;

	*pwd = NULL;
	*dir = NULL;
	return_value = 0;
	if (content->arg)
		return (is_arg(content, dir, saved_pwd));
	else if (!content->arg)
	{
		return_value = is_dash(content, dir, pwd, saved_pwd);
		if (return_value == O_ERROR)
			return (O_ERROR);
		if (return_value == 1)
			return (1);
		return_value = update_dash(content, dir, pwd, saved_pwd);
		if (return_value == O_ERROR)
			return (O_ERROR);
		if (return_value == 1)
			return (1);
	}
	return (1);
}

void	check_dir(t_content *content, char *pwd, char *saved_pwd, char *dir)
{
	printf("dir = %s\n", dir);
	if(!dir)
		return;
	if (access(dir, X_OK) == -1)
	{
		ft_putstr_fd("maxishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(content->arg[0], STDERR_FILENO);
		content->error_code = 1;
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
		clean_pwd(pwd, saved_pwd, NULL, content);
		free(dir);
		return ;
	}
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("maxishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(content->arg[0], STDERR_FILENO);
		ft_putendl_fd(": no such file or directory", STDERR_FILENO);
		content->error_code = 1;
	}
	free(dir);
}

void	ft_cd(t_content *content, t_list **env)
{
	char	*pwd;
	char	*saved_pwd;
	char	*dir;
	int		returned_value;

	saved_pwd = NULL;
	if (ft_tablen(content->cmd) != 1 && ft_strcmp(content->cmd[1], "-") != 0)
	{
		ft_putendl_fd("maxishell: cd: too many arguments", STDERR_FILENO);
		return ;
	}
	returned_value = load_dir(content, &dir, &pwd, &saved_pwd);
	if (returned_value == 0 || returned_value == O_ERROR)
		return ;
	check_dir(content, pwd, saved_pwd, dir);
	update_pwd(content, env, pwd, saved_pwd);
}
