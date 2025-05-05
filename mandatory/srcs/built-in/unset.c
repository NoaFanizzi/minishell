/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:38:54 by nofanizz          #+#    #+#             */
/*   Updated: 2025/05/05 13:01:19 by nofanizz         ###   ########.fr       */
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

int	ft_unset(t_list **env, t_content *content)
{
	t_env *link;
	t_list *current;
	t_env *temp;
	int	pos;
	int	i;

	i = 0;
	pos = ft_check_if_in_base(*env, content->arg);
	printf("pos = %d\n", pos);
	if(pos == -1)
		return(1);
	if(i != 0 && i != ft_lstsize(*env))
	{
		while(i < pos - 1)
		{
			current = *env;
			link = (t_env *)current->content;
			i++;
		}
		temp = (t_env *)current->next;
		current->next = current->next->next;
		ft_free_link(temp);
	}
	if(i == 0)
	{
		current = *env;
		link = (t_env *)current->content;
		temp = (t_env *)current->next;
		current->next = current->next->next;
		ft_free_link(temp);
	}
	if(i == ft_lstsize(*env))
	{
		while(i < pos - 1)
		{
			current = *env;
			link = (t_env *)current->content;
			i++;
		}
		temp = (t_env *)current->next;
		current->next = NULL;
		ft_free_link(temp);
	}
	return(0);
}

//a
//b
//c
//d
//e