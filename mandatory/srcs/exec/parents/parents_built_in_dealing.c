/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents_built_in_dealing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:54:27 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/31 12:49:16 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_built_in_dad(t_array *array, t_list **env)
{
	int	return_value;

	return_value = 0;
	if (ft_strcmp(array->content[0].cmd[0], "export") == 0)
		return_value = ft_export(env, &array->content[0]);
	if (ft_strcmp(array->content[0].cmd[0], "unset") == 0)
		return_value = ft_unset(env, &array->content[0]);
	if (ft_strcmp(array->content[0].cmd[0], "pwd") == 0)
		return_value = ft_pwd(&array->content[0]);
	if (ft_strcmp(array->content[0].cmd[0], "cd") == 0)
		ft_cd(&array->content[0], env);
	if (ft_strcmp(array->content[0].cmd[0], "echo") == 0)
		return_value = ft_echo(&array->content[0]);
	if ((ft_strcmp(array->content[0].cmd[0], "env") == 0
			&& ft_tablen(array->content[0].cmd) == 1)
		&& (!array->content[0].arg))
		ft_display_env(*env, &array->content[0]);
	return (return_value);
}

int	ft_is_built_in(t_content *content)
{
	if (!content->cmd || !content->cmd[0])
		return (1);
	if ((ft_strcmp(content->cmd[0], "export") == 0)
		|| (ft_strcmp(content->cmd[0], "unset") == 0)
		|| (ft_strcmp(content->cmd[0], "pwd") == 0)
		|| (ft_strcmp(content->cmd[0], "cd") == 0)
		|| (ft_strcmp(content->cmd[0], "echo") == 0)
		|| ((ft_strcmp(content->cmd[0], "env") == 0
				&& ft_tablen(content->cmd) == 1) && (!content->arg)))
		return (0);
	return (1);
}
