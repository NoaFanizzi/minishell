/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:05:10 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/19 11:23:55 by nofanizz         ###   ########.fr       */
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
	//ft_display_env(var);
	ft_parse_flags(argv);
	launch_shell(&var);
	ft_free_env(var);
	exit(0);
	//ft_test(&var, argc, argv);
	//ft_display_env(var);
	//ft_cd(&m_env, argv[1]);
	//ft_pwd();
	//ft_free_tab(var.env);
	//ft_cd(&m_env, argv[1]);
	//ft_test(argc, argv);
}