/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:16:50 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/26 20:24:14 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*dup_env_node(t_env *env)
{
	t_env	*dup;

	dup = malloc(sizeof * dup);
	if (!dup)
		return (NULL);
	dup->var = ft_strdup(env->var);
	if (env->arg)
		dup->arg = ft_strdup(env->arg);
	else
		dup->arg = NULL;
	if (env->op)
		dup->op = ft_strdup(env->op);
	else
		dup->op = NULL;
	dup->exp = env->exp;
	return (dup);
}

t_list	*dup_env_list(t_list *env)
{
	t_list	*copy;
	t_list	*new;
	t_env	*e;

	copy = NULL;
	while (env)
	{
		e = (t_env *)env->content;
		new = ft_lstnew(dup_env_node(e));
		if (!new)
		{
			ft_lstclear(&copy, ft_free_link);
			return (NULL);
		}
		ft_lstadd_back(&copy, new);
		env = env->next;
	}
	return (copy);
}
