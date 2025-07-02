/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:05:10 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/02 12:55:08 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_array *g_array = NULL;


int	main(int argc, char **argv, char **env)
{
	t_list *var;
	//t_array *array;
	
	(void)argc;
	(void)argv;
	//array = NULL;

	var = ft_init_env(env);
	launch_shell(&var);
	ft_free_env(var);
	exit(0);
}