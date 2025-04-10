/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:39:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/10 18:20:23 by nofanizz         ###   ########.fr       */
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
	return(link);
}

void	ft_get_var(t_export *temp, t_content *content)
{
	char *temp_value;
	size_t	i;
	size_t pos;
	
	i = 0;
	pos = ft_strrchr(content->arg, 61);
	temp->var = ft_calloc((i + 1), sizeof(char));
	while(i < pos)
	{
		temp->var[i] = content->arg[i];
		i++;
	}
	temp->var[i] = '\0';
	pos++;
	if(content->arg[pos] == '\0')
	{
		temp->status = 0;
		return;
	}
	temp_value = ft_strdup(&content->arg[pos]);
	temp->value = ft_atoi(temp_value);
	free(temp_value);
}

int	ft_is_a_value(char *str)
{
	size_t	i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if(str[i] == '=')
		i++;
	if(str[i] == '\0')
		return(1);
	return(0);
}

void	ft_export(t_list *env, t_content *content)
{
	t_env *link;
	size_t	pos;

	pos = ft_check_if_in_base(env, content->arg);
	if(pos == ft_lstsize(env)) // ca veut dire que c'etait pas dedans
	{
		link = ft_add_new_link(content->arg);
		ft_lstadd_back(&env, ft_lstnew(link));
		if(link->arg != NULL)
			link->exp = 1;
	}
	else //ca veut dire que c'etait deja dedans
	{
		while(pos > 0)
		{
			env = env->next;
			pos--;
		}
		link = (t_env *)env->content;
		if(link->arg == NULL) //si y'avait pas de value assigned a la variable
		{
			if(ft_is_a_value(env) == 1) //si y'a une value assigned a la variable qu'on est en train d'export
				//replace le maillon de la chaine correctement
			else
				return(NULL);
		}
		if(link->arg != NULL) // y'avait deja une value assigned
		{
			//append la value 
		}
	}
}
