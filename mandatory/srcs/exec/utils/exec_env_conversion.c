/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:51:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/25 11:22:20 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_env_length(t_list *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

int	ft_add_new_tab(t_list *env, char **converted, size_t i)
{
	t_env	*cpy;
	char	*temp;

	temp = NULL;
	cpy = (t_env *)env->content;
	if (cpy->op)
		temp = ft_strjoin(cpy->var, cpy->op);
	if (!temp)
		return (-1);
	if (!cpy->op)
		temp = ft_strdup(cpy->var);
	if (!temp)
		return (-1);
	if (cpy->arg)
		converted[i] = ft_strjoin(temp, cpy->arg);
	if (!cpy->arg)
		converted[i] = ft_strdup(temp);
	if (!converted)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	return (0);
}

char	**ft_convert_env(t_list *env)
{
	char	**converted;
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_env_length(env);
	converted = ft_calloc((length + 1), sizeof(char *)); // PROTECTED
	if (!converted)
		return (NULL);
	while (env)
	{
		if (ft_add_new_tab(env, converted, i) == -1)
		{
			free(converted);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	converted[i] = NULL;
	return (converted);
}
