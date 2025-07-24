/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:05:10 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/24 14:32:16 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0;


int	main(int argc, char **argv, char **env)
{
	t_list *var;
	int returned_value;
	//t_array *array;
	
	(void)argc;
	(void)argv;
	//array = NULL;

	//printf("fd max = %d\n", FD_SETSIZE);
	if(argc != 1)
		return(0);
	// if (!isatty(STDOUT) || !isatty(STDIN))
	// {
	// 	printf("minishell: not a tty\n");
	// 	exit(0);
	// }
	var = ft_init_env(env);
	returned_value = launch_shell(&var);
	ft_free_env(var);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(returned_value);
}