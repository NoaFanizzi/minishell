/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:54:12 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/26 14:43:00 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_test(int argc, char **argv)
{
	char **cmd;
	
	(void)argc;
	
	cmd = malloc(sizeof(char *) * (argc - 1));
	cmd[0] = ft_strdup(argv[1]);
	cmd[1] = ft_strdup(argv[2]);
	cmd[2] = ft_strdup(argv[3]);
	//printf("cmd[0] = %s\n", cmd[0]);
	//printf("cmd[1] = %s\n", cmd[1]);
	//printf("cmd[2] = %s\n", cmd[2]);

	ft_echo(cmd);
	//free(cmd);
}

int	main(int argc, char **argv, char **env)
{
	t_env m_env;
	
	(void)argc;
	(void)argv;
	ft_init_env(env, &m_env);
	ft_cd(&m_env, argv[1]);
	ft_pwd();
	ft_free_tab(m_env.var);
	//ft_cd(&m_env, argv[1]);
	//ft_display_env(m_env.var);
	//ft_test(argc, argv);
}

//TODO faire export
//TODO faire unset
//TODO faire exit