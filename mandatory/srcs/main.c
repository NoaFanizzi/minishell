/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:05:10 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/20 13:58:37 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **env)
{
	t_list	*var;
	int		returned_value;
	t_array	array;

	(void)argc;
	(void)argv;
	var = NULL;
	array.p_exit_status = 0;
	if (argc != 1)
		return (0);
	// if (!isatty(STDOUT) || !isatty(STDIN))
	// {
	// 	ft_putstr_fd("minishell: not a tty\n", 2);
	// 	exit(1);
	// }
	var = ft_init_env(env, &array);
	// display_header();
	returned_value = launch_shell(&var, &array);
	ft_free_env(var);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(returned_value);
}
