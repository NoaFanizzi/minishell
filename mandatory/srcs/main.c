/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:05:10 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/02 08:24:18 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;
int g_macro_debug = 0;


void	ft_parse_flags(char **argv)
{
	size_t	i;

	i = 0;
	while(argv[i])
	{
		if(ft_strncmp(argv[i], "redir", 5) == 0)
		{
			g_macro_debug = REDIR;
			return;
		}
		if(ft_strncmp(argv[i], "all", 3) == 0)
		{
			g_macro_debug = ALL;
			return;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_list *var;
	//t_array *array;
	
	(void)argc;
	(void)argv;
	//array = NULL;

	var = ft_init_env(env);
	ft_parse_flags(argv);
	launch_shell(&var);
	ft_free_env(var);
	exit(0);
}