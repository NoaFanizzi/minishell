/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:10:27 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/20 15:49:26 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_node(t_content *content, char **dir, char **pwd, char **saved_pwd)
{
	t_env	*node;

	node = get_env("PWD", *(content->env));
	if (node == NULL)
		*saved_pwd = NULL;
	else
	{
		*saved_pwd = ft_strdup(node->arg);
		if (!*saved_pwd)
		{
			ft_wipe(dir);
			return (ft_open_error(content, NULL));
		}
	}
	(void)*pwd;
	ft_putendl_fd(*dir, STDOUT_FILENO);
	return (1);
}

int	no_dir_to_update(t_content *content, char **dir, char **pwd,
		char **saved_pwd)
{
	t_env	*node;

	if (!*dir)
	{
		node = get_env("HOME", *(content->env));
		if (node == NULL)
		{
			clean_pwd(pwd, saved_pwd, "HOME", content);
			return (1);
		}
		ft_wipe(dir);
		*dir = ft_strdup(node->arg);
		if (!*dir)
		{
			ft_wipe(saved_pwd);
			return (ft_open_error(content, NULL));
		}
	}
	return (0);
}

int	update_dash(t_content *content, char **dir, char **pwd, char **saved_pwd)
{
	t_env	*node;

	node = get_env("PWD", *(content->env));
	if (node == NULL)
		*saved_pwd = NULL;
	else
	{
		ft_wipe(saved_pwd);
		*saved_pwd = ft_strdup(node->arg);
		if (!*saved_pwd)
		{
			ft_wipe(dir);
			return (ft_open_error(content, NULL));
		}
	}
	return (no_dir_to_update(content, dir, pwd, saved_pwd));
}

int	nod_in_dash(t_content *content, char **dir, char **pwd, char **saved_pwd)
{
	t_env	*node;

	node = get_env("OLDPWD", *(content->env));
	if (node && node->arg && node->arg[0])
	{
		*dir = ft_strdup(node->arg);
		if (!*dir)
			return (ft_open_error(content, NULL));
	}
	else
	{
		*dir = NULL;
		if (!node)
			clean_pwd(pwd, saved_pwd, "OLDPWD", content);
		else
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			clean_pwd(pwd, saved_pwd, NULL, content);
			content->error_code = 0;
			content->array_ptr->p_exit_status = 0;
		}
		return (1);
	}
	return (0);
}

int	is_dash(t_content *content, char **dir, char **pwd, char **saved_pwd)
{
	int	returned_value;

	if (content->cmd[1] && ft_strcmp(content->cmd[1], "-") == 0)
	{
		returned_value = nod_in_dash(content, dir, pwd, saved_pwd);
		if (returned_value != 0)
			return (returned_value);
		returned_value = is_node(content, dir, pwd, saved_pwd);
		if (returned_value == 0)
			return (0);
		if (returned_value == O_ERROR)
			return (O_ERROR);
	}
	return (0);
}
