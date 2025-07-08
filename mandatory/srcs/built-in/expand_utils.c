/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:17:18 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/08 17:32:33 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env *get_env(char *var_name, t_list *env)
{
	t_env *cpy;
	
	while(env)
	{
		cpy = (t_env *)env->content;
		if(ft_strcmp(cpy->var, var_name) == 0)
			return(cpy);
		env = env->next;
	}
	return(NULL);
}
int var_exists(char *var_name, t_list *env)
{
	if(get_env(var_name, env))
		return(1);
	return(0);
}

size_t	get_true_var_length(char *var_name, t_list *env)
{
	t_env *cpy;

	cpy = get_env(var_name, env);
	if(cpy)
		return(ft_strlen(cpy->arg));
	return(0);
}



char *get_var_value(char *var_name, t_list *env)
{
	t_env *cpy;

	cpy = get_env(var_name, env);
	if(cpy)
		return(ft_strdup(cpy->arg));
	return(NULL);
}