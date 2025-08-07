/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:22:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/07 16:53:58 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_saved_pwd(t_content *content, char **dir, char **saved_pwd)
{
	char	*temp;

	if (ft_strcmp(*saved_pwd, content->arg[0]) == 0)
	{
		*dir = ft_strdup(*saved_pwd); // PROTECTED
		return (0);
	}
	temp = ft_strjoin(*saved_pwd, "/"); // PROTECTED
	if (!temp)
	{
		ft_wipe(saved_pwd);
		return (ft_open_error(content, NULL));
	}
	*dir = ft_strjoin(temp, content->arg[0]); // PROTECTED
	ft_wipe(&temp);
	if (!*dir)
	{
		ft_wipe(saved_pwd);
		return (ft_open_error(content, NULL));
	}
	return (0);
}

int	is_arg(t_content *content, char **dir, char **saved_pwd)
{
	t_env	*node;

	*saved_pwd = getcwd(NULL, 0); // PROTECTED
	if (*saved_pwd)
		return (is_a_saved_pwd(content, dir, saved_pwd));
	else
	{
		node = get_env("PWD", *(content->env));
		if (node == NULL)
			*saved_pwd = NULL;
		else
		{
			*saved_pwd = ft_strdup(node->arg); // PROTECTED
			if (!*saved_pwd)
				return (ft_open_error(content, NULL));
		}
		*dir = ft_strdup(content->arg[0]); // PROTECTED
		if (!*dir)
		{
			ft_wipe(saved_pwd);
			return (ft_open_error(content, NULL));
		}
	}
	return (0);
}

int	load_dir(t_content *content, char **dir, char **pwd, char **saved_pwd)
{
	int	return_value;

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
	return (0);
}

int	print_dir_message(char *str1, char *str2, char *str3)
{
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	if (str3)
		ft_putstr_fd(str3, 2);
	return (1);
}

int	check_dir(t_content *content, char **dir)
{
	struct stat	sb;

	if (!*dir)
		return (1);
	if (stat(*dir, &sb) == -1)
	{
		ft_putstr_fd("maxishell: cd: ", STDERR_FILENO);
		perror(content->arg[0]);
		return (1);
	}
	else if (!S_ISDIR(sb.st_mode))
		return (print_dir_message("maxishell: cd: ",
				content->arg[0], ": Not a directory\n"));
	else if (access(*dir, X_OK) == -1)
		return (print_dir_message("maxishell: cd: ",
				content->arg[0], ": Permission denied\n"));
	else if (chdir(*dir) == -1)
		return (print_dir_message("maxishell: cd: ",
				content->arg[0], ": no such file or directory\n"));
	free(*dir);
	return (0);
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
	if (returned_value == 1 || returned_value == O_ERROR)
		return ;
	if (check_dir(content, &dir) == 1)
	{
		clean_pwd(&pwd, &saved_pwd, NULL, content);
		free(dir);
		content->error_code = 1;
		return ;
	}
	update_pwd(content, env, &pwd, &saved_pwd);
}
