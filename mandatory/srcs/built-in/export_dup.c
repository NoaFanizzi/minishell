/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:16:50 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/01 17:40:18 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *dup_env_node(t_env *e)
{
    t_env *dup = malloc(sizeof *dup);
    if (!dup) return NULL;
    dup->var   = ft_strdup(e->var);
    dup->arg   = e->arg ? ft_strdup(e->arg) : NULL;
    dup->op    = e->op  ? ft_strdup(e->op)  : NULL;
    dup->exp   = e->exp;
    return dup;
}

t_list *dup_env_list(t_list *env)
{
    t_list *copy = NULL;
    t_list *new;
    t_env  *e;
    while (env)
    {
        e = (t_env *)env->content;
        new = ft_lstnew(dup_env_node(e));
        if (!new)
        {
            ft_lstclear(&copy, ft_free_link);
            return NULL;
        }
        ft_lstadd_back(&copy, new);
        env = env->next;
    }
    return copy;
}
