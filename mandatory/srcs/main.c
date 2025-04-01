/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:54:12 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/01 14:33:00 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_test(int argc, char **argv)
// {
// 	char **cmd;
	
// 	(void)argc;
	
// 	cmd = malloc(sizeof(char *) * (argc - 1));
// 	cmd[0] = ft_strdup(argv[1]);
// 	cmd[1] = ft_strdup(argv[2]);
// 	cmd[2] = ft_strdup(argv[3]);
// 	//printf("cmd[0] = %s\n", cmd[0]);
// 	//printf("cmd[1] = %s\n", cmd[1]);
// 	//printf("cmd[2] = %s\n", cmd[2]);

// 	ft_echo(cmd);
// 	//free(cmd);
// }

int	ft_fill_test(t_content *content, int params)
{
	if(params == 0)
	{
		content->arg = ft_strdup("dracaufeu");
		content->cmd = malloc(sizeof(char *) * 1);
		content->cmd[0] = ft_strdup("cat");
		content->input = open("Makefile", O_RDONLY);
		content->output = -2;
	}
	if(params == 1)
	{
		content->arg = ft_strdup("tiplouf");
		content->cmd = malloc(sizeof(char *) * 1);
		content->cmd[0] = ft_strdup("cat");
		content->input = -2;
		content->output = open("test", O_RDWR, O_CREAT);
	}
	return(0);
}

int	ft_test(t_env *m_env)
{
	t_array array;
	t_expar expar;
	int	i;

	i = 0;
	array.size = 2;
	array.content = malloc(sizeof (t_content) * array.size);
	while(i < array.size)
	{
		ft_fill_test(&array.content[i], i);
		//printf("content->arg = %s\n", array.content[i].arg);
		//printf("content->cmd = %s\n", array.content[i].cmd[0]);
		i++;
	}
	ft_init_exec(&expar, m_env->var, &array);
	return(0);
}

int	main(int argc, char **argv, char **env)
{
	t_env m_env;
	
	(void)argc;
	(void)argv;
	ft_init_env(env, &m_env);
	ft_test(&m_env);
	//ft_cd(&m_env, argv[1]);
	//ft_pwd();
	ft_free_tab(m_env.var);
	//ft_cd(&m_env, argv[1]);
	//ft_display_env(m_env.var);
	//ft_test(argc, argv);
}

//TODO faire export
//TODO faire unset
//TODO faire exit