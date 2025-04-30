/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:51:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/29 15:27:03 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_env_length(t_list *env)
{
	size_t	i;

	i = 0;
	while(env)
	{
		env = env->next;
		i++;
	}
	return(i);
}
char	**ft_convert_env(t_list *env)
{
	t_env *cpy;
	char **converted;
	char *temp;
	size_t	i;
	size_t	length;
	
	i = 0;
	length = ft_env_length(env);
	printf("length = %zu\n", length);
	converted = ft_calloc((length + 1), sizeof(char *));
	if(!converted)
		return(NULL);
	while(env)
	{
		cpy = (t_env *)env->content;
		temp = ft_strjoin(cpy->var, cpy->op);
		if(!temp)
			return(NULL);
		converted[i] = ft_strjoin(temp, cpy->arg);
		if(!converted)
		{
			free(temp);
			return(NULL);
		}
		free(temp);
		i++;
		env = env->next;
	}
	converted[i] = NULL;
	return(converted);
}
