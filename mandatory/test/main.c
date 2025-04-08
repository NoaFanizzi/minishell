/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:05:10 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/08 17:48:59 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_new_link(char *env, t_env **link)
{
	size_t	i;
	size_t	length;

	i = 0;
	
	*link = ft_calloc(1, sizeof(t_env));
	while((env[i] != '+' && env[i] != '=')
		&&(env[i] != '\0'))
		i++;
	length = i;
	if(env[i] == '+')
	{
		(*link)->op = ft_strdup("+=");
		i += 2;
	}
	if(env[i] == '=')
	{
		(*link)->op = ft_strdup("=");
		i++;
	}
	(*link)->arg = ft_strdup(&env[i]);
	(*link)->var = ft_calloc((length + 1), sizeof(char));
	i = 0;
	while(i < length)
	{
		(*link)->var[i] = env[i];
		i++;
	}
	(*link)->var[i] = '\0';
}

void	ft_init_env(char **o_env, t_env *env)
{
	size_t	i;

	i = 0;
	env->next = NULL;
	// while(o_env[i])
	// 	i++;
	//var->env = malloc(sizeof(t_env) * (i + 1));
	//i = 0;
	// if(!(env->next))
	// 	ft_add_new_link(o_env[i], env->next);
	ft_add_new_link(o_env[i], &env);
	while(o_env[i])
	{
		ft_add_new_link(o_env[i], &env->next);
		env = env->next;
		i++;
	}
	env->next = NULL;
}

void	ft_display_env(t_env *env)
{
	size_t	i;

	i = 0;
	while(env->next != NULL)
	{
		ft_putstr_fd(env->var, 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env env;
	
	(void)argc;
	(void)argv;
	ft_init_env(env, &env);
	//ft_display_env(m_env.var);
	//ft_test(&env);
	//ft_cd(&m_env, argv[1]);
	//ft_pwd();
	//ft_free_tab(var.env);
	//ft_cd(&m_env, argv[1]);
	//ft_test(argc, argv);
}