/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/28 10:40:54 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

//check cases when there is one commnad, or nothing or idk but you understood

char	***parse_command(char *line, char **env)
{	
	char 	**command = NULL;
	char	***cmd_splitted = NULL;
	int		k;
	int		i;

	k = 0;
	command = quotes_splitting(command, line);
	free(line);
	if (!command)
		return (NULL);//error
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	printf("\n\n");
	command = space_splitting(command);
	if (!command)
		return (NULL);//error
	k = 0;
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	printf("\n\n");
	
	command = meta_splitting(command);
	if (!command)
		return (NULL);//error
	k = 0;
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	
	quotes_removal(command);
	if (!command)
		return (NULL);//error
	k = 0;
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	//LEAKS DONE UNTIL THERE
	//NEED TO FREE COMMAND BUT NOT FOR NOW
	cmd_splitted = command_splitting(command);
	if (!cmd_splitted)
		return (NULL);
	printf("\n\n");
	k = 0;
	while (cmd_splitted[k])
	{
		i = 0;
		printf("\ncommand n%d\n", k + 1);
		while (cmd_splitted[k][i])
		{
			printf("word n%d : %s\n", i + 1, cmd_splitted[k][i]);
			i++;
		}
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
	free_words(command);
	return (cmd_splitted);
}

void	analyse_command(char ***cmd_splitted)
{
	find_in_out_files();
	return ;
}

void	launch_shell(char **env)
{
	char	*line;
	char	***cmd_splitted;
	
	while (1)
	{
		line = readline("maxishell$ ");
		if (line == NULL)
			exit(0);
		cmd_splitted = parse_command(line, env);
		if (!cmd_splitted)
			return ;
	}
}
int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	launch_shell(env);
	return (0);
}