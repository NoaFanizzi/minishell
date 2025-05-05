/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:38:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/05/05 14:47:25 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_link(t_env *link)
{
	free(link->var);
	free(link->op);
	free(link->arg);
	free(link);
}

static void	ft_rm_first_link(t_list **env, t_content *content, int pos)
{
	int	i;
	t_list *temp;
	t_list *current;

	i = 0;
	temp = NULL;
	current = *env;
	while(i < pos - 1)
	{
		current = current->next;
		i++;
	}
	temp = current->next;
	current->next = current->next->next;
}
int	ft_unset(t_list **env, t_content *content)
{
	int	pos;
	int	i;

	i = 0;
	pos = ft_check_if_in_base(*env, content->arg);
	if(pos == -1)
		return(1);
	if(pos != 0)
		ft_rm_first_link(env, content, pos);
	else if(pos == 0)
	{
		temp = *env;
		*env = (*env)->next;
	}
	ft_lstdelone(temp, (void *)ft_free_link);
	return(0);
}

//a
//b
//c
//d
//e