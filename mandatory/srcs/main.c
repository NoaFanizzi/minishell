/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:05:10 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/10 15:31:10 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_test(t_list *env)
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
	ft_init_exec(env, &array);
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
	t_list *var;
	t_array *array;
	
	(void)argc;
	(void)argv;
	array = NULL;

	var = ft_init_env(env);
	ft_init_exec(var, array);
	ft_free_env(var);
	ft_test(var);
	//ft_display_env(var);
	//ft_cd(&m_env, argv[1]);
	//ft_pwd();
	//ft_free_tab(var.env);
	//ft_cd(&m_env, argv[1]);
	//ft_test(argc, argv);
}