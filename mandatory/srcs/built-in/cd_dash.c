/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:10:27 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/30 01:50:51 by nofanizz         ###   ########.fr       */
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
			free(*dir);
			return (ft_open_error(content, NULL));
		}
	}
	node = get_env("HOME", *(content->env));
	if (node == NULL)
	{
		clean_pwd(*pwd, *saved_pwd, "HOME", content);
		return (0);
	}
	ft_putendl_fd(*dir, STDOUT_FILENO);
	return (1);
}

int	update_dash(t_content *content, char **dir, char **pwd, char **saved_pwd)
{
	t_env	*node;

	node = get_env("PWD", *(content->env));
	if (node == NULL)
		*saved_pwd = NULL;
	else
	{
		*saved_pwd = ft_strdup(node->arg);
		if (!*saved_pwd)
			return (ft_open_error(content, NULL));
	}
	node = get_env("HOME", *(content->env));
	if (node == NULL)
	{
		clean_pwd(*pwd, *saved_pwd, "HOME", content);
		return (0);
	}
	*dir = ft_strdup(node->arg);
	if (!*dir)
	{
		free(*saved_pwd);
		return (ft_open_error(content, NULL));
	}
	return (1);
}

int	is_dash(t_content *content, char **dir, char **pwd, char **saved_pwd)
{
	t_env	*node;
	int		returned_value;

	(void)saved_pwd;
	(void)pwd;
	if (content->cmd[1] && ft_strcmp(content->cmd[1], "-") == 0)
	{
		node = get_env("OLDPWD", *(content->env));
		if (node)
		{
			*dir = ft_strdup(node->arg);
			if (!*dir)
				return (ft_open_error(content, NULL));
		}
		else
			*dir = NULL;
		returned_value = is_node(content, dir, pwd, saved_pwd);
		if (returned_value == 0)
			return (0);
		if (returned_value == O_ERROR)
			return (O_ERROR);
	}
	return (0);
}
