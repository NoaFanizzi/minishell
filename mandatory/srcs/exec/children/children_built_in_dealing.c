/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_built_in_dealing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:05:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/25 14:45:31 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_exit(t_content *content)
{
	if (content->arg)
		content->error_code = ft_atoi(content->arg[0]);
	else
		content->error_code = 0;
	ft_exit(content);
}

int	ft_is_built_in_child(t_content *content, t_list **env)
{
	int	return_value;

	return_value = 0;
	if (!content->cmd || !content->cmd[0])
		return (1);
	if (ft_strcmp(content->cmd[0], "echo") == 0)
		return_value = ft_echo(content);
	else if (ft_strcmp(content->cmd[0], "export") == 0)
		return_value = ft_export(env, content);
	else if (ft_strcmp(content->cmd[0], "env") == 0)
		ft_display_env(*env, content);
	else if (ft_strcmp(content->cmd[0], "unset") == 0)
		return_value = ft_unset(env, content);
	else if (ft_strcmp(content->cmd[0], "pwd") == 0)
		ft_pwd(content);
	else if (ft_strcmp(content->cmd[0], "cd") == 0)
		ft_cd(content, env); // TODO check les retours d'erreur pour le cd
	else if (ft_strcmp(content->cmd[0], "exit") == 0)
		manage_exit(content);
	else
		return (0);
	content->error_code = return_value;
	ft_exit(content);
	return (0);
}
