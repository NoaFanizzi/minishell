/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:05:10 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/17 17:15:24 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;


// int	ft_fill_test(t_content *content, int params)
// {
// 	if(params == 0)
// 	{
// 		content->cmd = malloc(sizeof(char *) * 4);
// 		content->cmd[0] = ft_strdup("cat");
// 		content->cmd[1] = NULL;
// 		content->cmd[2] = NULL;//NULL;//ft_strdup("dracaufeu");
// 		content->cmd[3] = NULL;
// 		content->arg = ft_strdup("Makefile");//ft_strdup("Makefile");//NULL;//ft_strdup("dracaufeu");
// 		content->files = NULL;
// 		content->size = 1;
// 		content->infile = -2;
// 		content->outfile = -2;
// 		//content->files = ft_calloc(2, sizeof(t_files));
// 		//content->files[0].index = 1;//open("test", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 		//content->files[0].type = PIPE;

// 		// content->cmd = malloc(sizeof(char *) * 4);
// 		// content->cmd[0] = ft_strdup("pwd");
// 		// content->cmd[1] = NULL; //ft_strdup("-e");
// 		// content->cmd[2] = NULL;//ft_strdup("dracaufeu");
// 		// content->cmd[3] = NULL;
// 		// content->arg = ft_strdup("test");//NULL;//ft_strdup("dracaufeu");
// 		// content->input = open("Makefile", O_RDONLY);
// 		// content->output = open("test", O_RDWR);
// 		//content->size = 1;
// 	}
// 	// if(params == 1)
// 	// {
// 	// 	content->cmd = malloc(sizeof(char *) * 4);
// 	// 	content->cmd[0] = ft_strdup("echo");
// 	// 	content->cmd[1] = NULL; //ft_strdup("-e");
// 	// 	content->cmd[2] = NULL;//ft_strdup("dracaufeu");
// 	// 	content->cmd[3] = NULL;
// 	// 	content->arg = ft_strdup("mardi");//NULL;//ft_strdup("dracaufeu");
// 	// 	content->files = NULL;
// 	// 	content->infile = -2;
// 	// 	content->outfile = -2;
// 	// }
// 	// if(params == 1)
// 	// {
// 	// 	content->cmd = malloc(sizeof(char *) * 4);
// 	// 	content->cmd[0] = ft_strdup("cat");
// 	// 	content->cmd[1] = ft_strdup("-e");
// 	// 	content->cmd[2] = NULL;//ft_strdup("tiplouf");
// 	// 	content->cmd[3] = NULL;
// 	// 	content->arg = NULL; //ft_strdup("tiplouf");
// 	// 	content->input = -2;
// 	// 	content->output = open("test", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	// }
// 	return(0);
// }

// int	ft_test(t_list **env, int argc, char **argv)
// {
// 	t_array array;
// 	int	i;

// 	i = 0;
// 	array.size = 1;
// 	(void)argc;
// 	array.content = malloc(sizeof (t_content) * array.size);
// 	while(i < array.size)
// 	{
// 		ft_fill_test(&array.content[i], i);
// 		// printf("content->arg = %s\n", array.content[i].arg);
// 		// printf("content->cmd = %s\n", array.content[i].cmd[0]);
// 		i++;
// 	}
// 	ft_init_exec(env, &array, argv);
// 	return(0);
// 	//i = 0;
// 	// while(i < array.size)
// 	// {
// 	// 	free(array.content[i].cmd[0]);
// 	// 	free(array.content[i].cmd[1]);
// 	// 	free(array.content[i].cmd[2]); // Si non NULL
// 	// 	free(array.content[i].cmd[3]); // Si non NULL
// 	// 	free(array.content[i].arg);
// 	// 	free(array.content[i].cmd); // Libère le tableau mallocé
// 	// 	close(array.content[i].input); // Fermeture des descripteurs
// 	// 	close(array.content[i].output);

// 	// 	//ft_free_content(&array.content[i]);
// 	// 	i++;
// 	// }
// 	//free(array.content);
// 	return(0);
// }


int	main(int argc, char **argv, char **env)
{
	t_list *var;
	//t_array *array;
	
	(void)argc;
	(void)argv;
	//array = NULL;

	var = ft_init_env(env);
	//ft_display_env(var);
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