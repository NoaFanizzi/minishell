/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/16 17:39:09 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

//check cases when there is one commnad, or nothing or idk but you understood

void	parse_command(char *line, char **env)
{	
	char 	**command = NULL;
	char	***cmd_splitted = NULL;
	int		k;

	k = 0;
	command = quotes_splitting(command, line);
	free(line);
	if (!command)
		return ;//error
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	printf("\n\n");
	command = space_splitting(command);
	if (!command)
		return ;//error
	k = 0;
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	printf("\n\n");
	//LEAKS DONE UNTIL THERE
	command = meta_splitting(command);
	if (!command)
		return ;//error
	k = 0;
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	command = quotes_removal(command);
	if (!command)
		return ;//error
	k = 0;
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	printf("\n\n");
	k = 0;
	while (command[k])
	{
		if (ft_try(env, command[k]) == 0)
			printf("%s is a command\n", command[k]);
		k++;
	}
	cmd_splitted = command_splitting(command);
	if (!cmd_splitted)
		return ;
	// free_words(command, k);
}

void	launch_shell(char **env)
{
	char	*line;
	
	while (1)
	{
		line = readline("maxishell$ ");
		if (line == NULL)
			exit(0);
		parse_command(line, env);
	}
}
int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	launch_shell(env);
	return (0);
}