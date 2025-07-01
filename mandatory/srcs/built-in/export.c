/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:39:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/01 17:28:54 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_in_base(t_list *env, char *str)
{
	size_t	i;
	size_t	link;
	t_env *cpy;

	i = 0;
	link = 0;
	while(str[i] && str[i] != '=')
		i++;
	while(env)
	{
		cpy = (t_env *)env->content;
		if((ft_strncmp(cpy->var, str, i) == 0)
			&& (ft_strlen(cpy->var) == i))
			return(link);
		env = env->next;
		link++;
	}
	return(-1);
}

int	ft_is_a_value(char *str)
{
	size_t	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '=')
			return(1);
		i++;
	}
	if(str[i] == '\0')
		return(0);
	return(0);
}

int	ft_is_chr(char *str, char c)
{
	size_t	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return(i);
		i++;
	}
	return(-1);
}


int	ft_check_if_first_nod(t_list *first_nod, t_list *previous)
{
	t_env *casted_first;
	t_env *casted_previous;

	casted_first = (t_env *)first_nod->content;
	casted_previous = (t_env *)previous->content;
	if(ft_strcmp(casted_first->var, casted_previous->var) == 0)
		return(1);
	return(0);
}

void ft_display_export(t_list *env_copy)
{
    t_list *head = env_copy;
    t_list *iter;
    t_list *min;
    t_list *prev;
    t_list *prev_min;
    t_env  *e;

    while (head)
    {
        min      = head;
        prev_min = NULL;
        prev     = head;
        iter     = head->next;

        while (iter)
        {
            e = (t_env *)iter->content;
            if (ft_strcmp(e->var, ((t_env *)min->content)->var) < 0)
            {
                prev_min = prev;
                min      = iter;
            }
            prev = iter;
            iter = iter->next;
        }

        e = (t_env *)min->content;
        if (e->arg)
        {
            ft_putstr_fd("export ", 1);
            ft_putstr_fd(e->var,    1);
            ft_putstr_fd("=\"",      1);
            ft_putstr_fd(e->arg,    1);
            ft_putstr_fd("\"\n",     1);
        }
        else
        {
            ft_putstr_fd("export ", 1);
            ft_putstr_fd(e->var,      1);
            ft_putstr_fd("\n",         1);
        }

        if (prev_min)
            prev_min->next = min->next;
        else
            head = min->next;

        ft_lstdelone(min, ft_free_link);
    }
}

int	is_number(char c)
{
	if(c >= '0' && c <= '9')
		return(1);
	return(0);
}

int	ft_check_var_validity(char *var)
{
	size_t	i;

	i = 0;
	while(var[i])
	{
		if(is_number(var[i]) == 1)
			return(1);
		i++;
	}
	return(0);
}

int	ft_init_export(t_list **env, t_content *content, size_t	i)
{
	t_env *link;
	t_list *current;
	int	pos;

	if(ft_check_var_validity(content->arg[i]) == 1)
	{
		ft_putstr_fd("maxishell: export: `", STDERR_FILENO);
		ft_putstr_fd(content->arg[i], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		content->error_code = 1;
		return(1);
	}
	pos = ft_check_if_in_base(*env, content->arg[i]); // ça me return la position de où c'est dans la liste
	if(pos == -1) // ca veut dire que c'etait pas dedans
	{
		link = ft_add_new_link(content->arg[i]);
		ft_lstadd_back(env, ft_lstnew(link));
		if(link->arg != NULL)
			link->exp = 1;
	}
	else //ca veut dire que c'etait deja dedans
	{
		current = *env;
		while(pos > 0)
		{
			current = current->next;
			pos--;
		}
		link = (t_env *)current->content;
		if(ft_is_a_value(content->arg[i]) == 1) 
		{
			free(link->arg);
			fill_env_arg(&link, content->arg[i], 0);
		}
	}
	content->error_code = 0;
	return(0);
}
int	ft_export(t_list **env, t_content *content)
{
	size_t	i;

	i = 0;
	t_list *cpy;

	if(content->arg == NULL)
	{
		cpy = dup_env_list(*env);
		ft_display_export(cpy);
		return(0);
	}
	while(content->arg[i])
	{
		ft_init_export(env, content, i);
		i++;
	}
	return(0);
}
