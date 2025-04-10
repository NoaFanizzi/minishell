/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/10 10:59:12 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	parse_command(char *line)
{	
	char 	**command = NULL;
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
	//LEAKS DONE UNTIL THERE
	free_words(command, k);
}

void	launch_shell(void)
{
	char	*line;
	
	while (1)
	{
		line = readline("maxishell$ ");
		if (line == NULL)
			exit(0);
		parse_command(line);
	}
}
int	main(void)
{
	launch_shell();
	return (0);
}