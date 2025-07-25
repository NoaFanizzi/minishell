/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:58:04 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/25 12:12:31 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_right_op(t_env *link, char *env, size_t i)
{
	free((link)->op);
	(link)->op = NULL;
	if (env[i] == '\0')
		(link)->op = NULL;
	if (env[i] == '+' && env[i + 1] == '=')
	{
		(link)->op = ft_strdup("+=");
		i += 2;
	}
	if (env[i] == '=')
	{
		(link)->op = ft_strdup("=");
		i++;
	}
	return (i);
}

int	ft_get_right_arg(t_env *link, char *env, size_t i)
{
	(link)->arg = NULL;
	if (env[i] == '\0')
		(link)->arg = NULL;
	if (env[i] != '\0')
		(link)->arg = ft_strdup(&env[i]);
	else if ((link)->op)
		(link)->arg = ft_strdup("");
	return (i);
}

t_env	*fill_env_arg(t_env **link, char *env, size_t *var_len)
{
	size_t	i;

	i = 0;
	while ((env[i] != '+' && env[i] != '=') && (env[i] != '\0'))
		i++;
	if (var_len)
		*var_len = i;
	i = ft_get_right_op(*link, env, i);
	ft_get_right_arg(*link, env, i);
	return (*link);
}

t_env	*ft_add_new_link(char *env)
{
	size_t	length;
	t_env	*link;

	link = ft_calloc(1, sizeof(t_env)); // PROTECTED
	if (!link)
		return (NULL);
	length = 0;
	(link)->op = 0;
	link = fill_env_arg(&link, env, &length);
	(link)->var = ft_substr(env, 0, length); // PROTECTED
	if (!link->var)
	{
		free(link->arg);
		free(link->var);
		free(link->op);
		free(link);
		return (NULL);
	}
	return (link);
}

t_list	*ft_init_env(char **o_env)
{
	size_t	i;
	t_list	*env;
	t_env	*new_env;

	env = NULL;
	i = 0;
	if (!o_env)
	{
		env = NULL;
		return (env);
	}
	while (o_env[i])
	{
		new_env = ft_add_new_link(o_env[i]);
		if (!new_env)
			return (NULL);
		if (ft_lstadd_back(&env, ft_lstnew(new_env)) == 1)
		{
			ft_free_one_chain_element(new_env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
