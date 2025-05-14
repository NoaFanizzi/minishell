/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:58:04 by nofanizz          #+#    #+#             */
/*   Updated: 2025/05/08 16:31:22 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_right_op(t_env *link, char *env, size_t i)
{
	if(env[i] == '+' && env[i+1] == '=')
	{
		(link)->op = ft_strdup("+=");
		i += 2;
	}
	if(env[i] == '=')
	{
		(link)->op = ft_strdup("=");
		i++;
	}

	return(i);
}

int	ft_get_right_arg(t_env *link, char *env, size_t	i)
{
	if(env[i] == '\0')
		(link)->arg = NULL;
	else if(env[i] != '\0')
		(link)->arg = ft_strdup(&env[i]);
	return(i);
}

t_env	*ft_add_new_link(char *env)
{
	size_t	i;
	size_t	length;
	t_env *link;

	i = 0;
	link = ft_calloc(1, sizeof(t_env));
	(link)->exp = 0;
	while((env[i] != '+' && env[i] != '=')
		&&(env[i] != '\0'))
		i++;
	length = i;
	i = ft_get_right_op(link, env, i);
	i = ft_get_right_arg(link, env, i);
	(link)->var = ft_calloc((length + 1), sizeof(char));
	i = 0;
	while(i < length)
	{
		(link)->var[i] = env[i];
		i++;
	}
	(link)->var[i] = '\0';
	return(link);
}

t_list	*ft_init_env(char **o_env)
{
	size_t	i;
	t_list *env;
	t_env	*new_env;

	env = NULL;
	i = 0;
	while(o_env[i])
	{
		new_env = ft_add_new_link(o_env[i]);
		ft_lstadd_back(&env, ft_lstnew(new_env));
		i++;
	}
	//env->next = NULL;
	return(env);
}

void	ft_display_env(t_list *env)
{
	t_env *cpy;

	while(env)
	{
		cpy = (t_env *)env->content;
		ft_putstr_fd(cpy->var, 1);
		ft_putstr_fd(cpy->op, 1);
		ft_putstr_fd(cpy->arg, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}
