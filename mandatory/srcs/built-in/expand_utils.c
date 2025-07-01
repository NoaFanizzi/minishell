/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:17:18 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/01 15:51:47 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


size_t	get_true_var_length(char *var_name, t_list *env)
{
	t_env *cpy;

	cpy = (t_env *)env->content;
	if((ft_strncmp(cpy->var, var_name, ft_strlen(cpy->var)) == 0)
		&&(ft_strlen(cpy->var) == ft_strlen(var_name)))
		return(ft_strlen(cpy->arg));
	env = env->next;
	while(env->next)
	{
		cpy = (t_env *)env->content;
		if((ft_strncmp(cpy->var, var_name, ft_strlen(cpy->var)) == 0)
		&&(ft_strlen(cpy->var) == ft_strlen(var_name)))
			return(ft_strlen(cpy->arg));
		env = env->next;
	}
	return(0);
}

int var_exists(char *var_name, t_list *env)
{
	t_env *cpy;
	
	while(env->next)
	{
		cpy = (t_env *)env->content;
		//printf("cpy->var = %s\n", cpy->var);
		if(ft_strcmp(cpy->var, var_name) == 0)
			return(1);
		env = env->next;
	}
	return(0);
}

char *get_var_value(char *var_name, t_list *env)
{
	t_env *cpy;
	char *var_returned;

	var_returned = NULL;
	cpy = (t_env *)env->content;
	if((ft_strncmp(cpy->var, var_name, ft_strlen(cpy->var)) == 0)
		&&(ft_strlen(cpy->var) == ft_strlen(var_name)))
		{
			var_returned = ft_strdup(cpy->arg);
			return(var_returned);
		}
	env = env->next;
	while(env->next)
	{
		cpy = (t_env *)env->content;
		if((ft_strncmp(cpy->var, var_name, ft_strlen(cpy->var)) == 0)
		&&(ft_strlen(cpy->var) == ft_strlen(var_name)))
		{
			var_returned = ft_strdup(cpy->arg);
			return(var_returned);
		}
		env = env->next;
	}
	return(NULL);
}