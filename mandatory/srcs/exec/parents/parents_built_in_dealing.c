/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents_built_in_dealing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:54:27 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/18 12:50:57 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_built_in_dad(t_array *array, t_list **env)
{
	if(ft_strcmp(array->content[0].cmd[0], "export") == 0)
		ft_export(env, &array->content[0]);
	if(ft_strcmp(array->content[0].cmd[0], "unset") == 0)
		ft_unset(env, &array->content[0]);
	if(ft_strcmp(array->content[0].cmd[0], "pwd") == 0)
		ft_pwd(&array->content[0]);
	if(ft_strcmp(array->content[0].cmd[0], "cd") == 0)
		ft_cd(&array->content[0], env);
	if(ft_strcmp(array->content[0].cmd[0], "echo") == 0)
		ft_echo(&array->content[0]);
	if(ft_strcmp(array->content[0].cmd[0], "env") == 0)
		ft_display_env(*env, &array->content[0]);
}

int	ft_is_built_in(t_content *content)
{
	if (!content->cmd || !content->cmd[0])
		return (1);
	if((ft_strcmp(content->cmd[0], "export") == 0)
		||(ft_strcmp(content->cmd[0], "unset") == 0)
		||(ft_strcmp(content->cmd[0], "pwd") == 0)
		||(ft_strcmp(content->cmd[0], "cd") == 0)
		||(ft_strcmp(content->cmd[0], "echo") == 0)
		||(ft_strcmp(content->cmd[0], "env") == 0))
		return(0);
	return(1);
}
