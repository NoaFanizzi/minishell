/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents_built_in_dealing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:54:27 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/02 07:59:21 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_built_in_dad(t_array *array, t_list **env)
{
	if(ft_strcmp(array->content->cmd[0], "export") == 0)
		ft_export(env, &array->content[0]);
	if(ft_strcmp(array->content->cmd[0], "unset") == 0)
		ft_unset(env, &array->content[0]);
	if(ft_strcmp(array->content->cmd[0], "pwd") == 0)
		ft_pwd();
	if(ft_strcmp(array->content->cmd[0], "cd") == 0)
		ft_cd(&array->content[0], env);
	if(ft_strcmp(array->content->cmd[0], "echo") == 0)
		ft_echo(&array->content[0]);
	if(ft_strcmp(array->content->cmd[0], "env") == 0)
		ft_display_env(*env, &array->content[0]);
}

int	ft_is_built_in(t_content *content)
{
	if (!content->cmd || !content->cmd[0])
		return (1);
	if((ft_strncmp(content->cmd[0], "export", 6) == 0 && ft_strlen(content->cmd[0]) == 6)
		||(ft_strncmp(content->cmd[0], "unset", 5) == 0 && ft_strlen(content->cmd[0]) == 5)
		||(ft_strncmp(content->cmd[0], "pwd", 3) == 0 && ft_strlen(content->cmd[0]) == 3)
		||(ft_strncmp(content->cmd[0], "cd", 2) == 0 && ft_strlen(content->cmd[0]) == 2)
		||(ft_strncmp(content->cmd[0], "echo", 4) == 0 && ft_strlen(content->cmd[0]) == 4)
		||(ft_strncmp(content->cmd[0], "env", 3) == 0 && ft_strlen(content->cmd[0]) == 3))
		return(0);
	return(1);
}
