/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:38:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/24 12:57:22 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// unset.c
#include "minishell.h"

void	ft_free_link(void *content)
{
    t_env *link = (t_env *)content;
    if (link->var)
        free(link->var);
    if (link->op)
        free(link->op);
    if (link->arg)
        free(link->arg);
    free(link);
}


// void	ft_rm_link(t_list **env, int pos)
// {
// 	int	i;
// 	t_list *temp;
// 	t_list *current;

// 	i = 0;
// 	temp = NULL;
// 	current = *env;
// 	while(i < pos - 1)
// 	{
// 		current = current->next;
// 		i++;
// 	}
// 	temp = current->next;
// 	current->next = current->next->next;
// 	ft_lstdelone(temp, (void *)ft_free_link);
// }

// unset.c (toujours)


void	ft_rm_link(t_list **env, int pos)
{
    t_list *prev;
    t_list *to_del;
    int     i;

    if (!env || !*env || pos < 0)
        return;

    if (pos == 0)
    {
        ft_rm_first_link(env);
        return;
    }

    prev = *env;
    i = 0;
    while (prev && i < pos - 1)
    {
        prev = prev->next;
        i++;
    }

    if (!prev || !prev->next)
        return;

    // 5) Détacher et supprimer
    to_del      = prev->next;
    prev->next  = to_del->next;
    ft_lstdelone(to_del, ft_free_link);
}


void	ft_rm_first_link(t_list **env)
{
	//int	i;
	t_list *temp;
	//t_list *current;

	//i = 0;
	temp = NULL;
	//current = *env;
	temp = *env;
	*env = (*env)->next;
	ft_lstdelone(temp, (void *)ft_free_link);
}


int	ft_init_unset(t_list **env, t_content *content, size_t	i)
{
	int	pos;

	pos = ft_check_if_in_base(*env, content->arg[i]);
	if(pos == -1)
		return(1);
	if(pos != 0)
		ft_rm_link(env, pos);
	else if(pos == 0)
		ft_rm_first_link(env);
	return(0);
}
int	ft_unset(t_list **env, t_content *content)
{
	size_t	i;

	i = 0;
	while(content->arg[i])
	{
		ft_init_unset(env, content, i);
		i++;	
	}
	return(0);
}
