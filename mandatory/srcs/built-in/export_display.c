/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:28:09 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/25 14:31:28 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_var_validity(char *var)
{
	size_t	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (1);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_if_first_nod(t_list *first_nod, t_list *previous)
{
	t_env	*casted_first;
	t_env	*casted_previous;

	casted_first = (t_env *)first_nod->content;
	casted_previous = (t_env *)previous->content;
	if (ft_strcmp(casted_first->var, casted_previous->var) == 0)
		return (1);
	return (0);
}

t_list	*find_min_node(t_list *start_node, t_list **prev_min_node)
{
	t_list	*iter;
	t_list	*prev;
	t_list	*min;
	t_env	*current_env;
	t_env	*min_env;

	iter = start_node->next;
	prev = start_node;
	min = start_node;
	*prev_min_node = NULL;
	while (iter)
	{
		current_env = (t_env *)iter->content;
		min_env = (t_env *)min->content;
		if (ft_strcmp(current_env->var, min_env->var) < 0)
		{
			*prev_min_node = prev;
			min = iter;
		}
		prev = iter;
		iter = iter->next;
	}
	return (min);
}

void	print_export_line(t_env *env_var)
{
	ft_putstr_fd("export ", 1);
	ft_putstr_fd(env_var->var, 1);
	if (env_var->arg)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env_var->arg, 1);
		ft_putstr_fd("\"\n", 1);
	}
	else
	{
		ft_putstr_fd("\n", 1);
	}
}

void	ft_display_export(t_list *env_list)
{
	t_list	*head;
	t_list	*prev_min;
	t_list	*min;
	t_env	*env_var;

	head = env_list;
	while (head)
	{
		prev_min = NULL;
		min = find_min_node(head, &prev_min);
		env_var = (t_env *)min->content;
		print_export_line(env_var);
		if (prev_min)
			prev_min->next = min->next;
		else
			head = min->next;
		ft_lstdelone(min, ft_free_link);
	}
}
