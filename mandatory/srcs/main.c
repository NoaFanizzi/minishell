/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:54:12 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/02 13:21:15 by nofanizz         ###   ########.fr       */
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
		content->cmd = malloc(sizeof(char *) * 4);
		content->cmd[0] = ft_strdup("cat");
		content->cmd[1] = ft_strdup("-e");
		content->cmd[2] = NULL;//ft_strdup("dracaufeu");
		content->cmd[3] = NULL;
		content->arg = NULL;//ft_strdup("dracaufeu");
		content->input = open("Makefile", O_RDONLY);
		content->output = -2;
	}
	if(params == 1)
	{
		content->cmd = malloc(sizeof(char *) * 4);
		content->cmd[0] = ft_strdup("echo");
		content->cmd[1] = ft_strdup("-n");
		content->cmd[2] = NULL;//ft_strdup("tiplouf");
		content->cmd[3] = NULL;
		content->arg = ft_strdup("tiplouf");
		content->input = -2;
		content->output = open("test", O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	return(0);
}

int	ft_test(t_env *m_env)
{
	t_array array;
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
	ft_init_exec(m_env->var, &array);
	return(0);
	// i = 0;
	// while(i < array.size)
	// {
	// 	printf("i = %d\n", i);
	// 	//ft_free_content(&array.content[i]);
	// 	i++;
	// }
	// free(array.content);
	// return(0);
}

int	main(int argc, char **argv, char **env)
{
	t_env m_env;
	
	(void)argc;
	(void)argv;
	ft_init_env(env, &m_env);
	//ft_display_env(m_env.var);
	ft_test(&m_env);
	//ft_cd(&m_env, argv[1]);
	//ft_pwd();
	ft_free_tab(m_env.var);
	//ft_cd(&m_env, argv[1]);
	//ft_test(argc, argv);
}

//TODO faire export
//TODO faire unset
//TODO faire exit