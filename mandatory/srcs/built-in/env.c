/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:58:04 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/28 14:30:13 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_right_op(t_env *link, char *env, size_t i)
{
	free((link)->op);
	(link)->op = NULL;
	if (env[i] == '\0')
		(link)->op = NULL;
	if (env[i] == '=')
	{
		(link)->op = ft_strdup("="); // PROTECTED
		if (!link->op)
			return (-1);
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
	{
		(link)->arg = ft_strdup(&env[i]); // PROTECTED
		if (!link->arg)
			return (-1);
	}
	else if ((link)->op)
	{
		(link)->arg = ft_strdup(""); // PROTECTED
		if (!link->arg)
		{
			free(link->op);
			return (-1);
		}
	}
	return (i);
}

int	fill_env_arg(t_env **link, char *env, size_t *var_len)
{
	long long	i;

	i = 0;
	while ((env[i] != '+' && env[i] != '=') && (env[i] != '\0'))
		i++;
	if (var_len)
		*var_len = i;
	i = ft_get_right_op(*link, env, i);
	if (i == -1)
		return (1);
	if (ft_get_right_arg(*link, env, i) == -1)
		return (1);
	return (0);
}

t_env	*ft_add_new_link(char *env, t_array *array)
{
	size_t	length;
	t_env	*link;

	link = ft_calloc(1, sizeof(t_env)); // PROTECTED
	if (!link)
	{
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		array->p_exit_status = 1;
		return (NULL);
	}
	length = 0;
	link->op = NULL;
	link->var = NULL;
	link->arg = NULL;
	if (fill_env_arg(&link, env, &length) == 1)
		return (ft_free_one_chain_element(link, array));
	(link)->var = ft_substr(env, 0, length); // PROTECTED
	if (!link->var)
		return (ft_free_one_chain_element(link, array));
	return (link);
}

t_list	*ft_init_env(char **o_env, t_array *array)
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
		new_env = ft_add_new_link(o_env[i], array);
		if (!new_env)
			return (NULL);
		if (ft_lstadd_back(&env, ft_lstnew(new_env)) == 1)
			return (ft_free_one_chain_element(new_env, array));
		i++;
	}
	return (env);
}
