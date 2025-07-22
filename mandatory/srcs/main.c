/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:05:10 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/22 17:54:59 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0;


int	main(int argc, char **argv, char **env)
{
	t_list *var;
	//t_array *array;
	
	(void)argc;
	(void)argv;
	//array = NULL;

	//printf("fd max = %d\n", FD_SETSIZE);
	if(argc != 1)
		return(0);
	if (!isatty(STDOUT) || !isatty(STDIN))
	{
		printf("minishell: not a tty\n");
		exit(0);
	}
	var = ft_init_env(env);
	launch_shell(&var);
	ft_free_env(var);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(0);
}