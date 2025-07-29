/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:17:18 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/29 17:49:19 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env(char *var_name, t_list *env)
{
	t_env	*cpy;

	while (env)
	{
		cpy = (t_env *)env->content;
		if (ft_strcmp(cpy->var, var_name) == 0)
			return (cpy);
		env = env->next;
	}
	return (NULL);
}

int	var_exists(char *var_name, t_list *env)
{
	if (get_env(var_name, env) != NULL)
		return (1);
	return (0);
}

size_t	get_true_var_length(char *var_name, t_list *env)
{
	t_env	*cpy;

	if (ft_strcmp(var_name, "$?") == 0)
		return (ft_strlen(var_name));
	cpy = get_env(var_name, env);
	if (cpy)
		return (ft_strlen(cpy->arg));
	return (0);
}

char	*get_var_value(char *var_name, t_list *env)
{
	t_env	*cpy;
	char *var;

	cpy = get_env(var_name, env);
	if (cpy)
	{
		var = NULL; //ft_strdup(cpy->arg); //PROTECTED
		if(!var)
		{
			ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
			return(NULL);
		}
		return (var);
	}
	return (NULL);
}

int	ft_is_a_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	if (str[i] == '\0')
		return (0);
	return (0);
}
