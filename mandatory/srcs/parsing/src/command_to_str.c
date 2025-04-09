/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/09 17:59:08 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	parse_command(char *line)
{	
	char 	**command = NULL;
	int		k;

	k = 0;
	(void)line;
	command[0] = "echo";
	command[1] = "\"$VAR\"";
	command[2] = "| grep -o";
	command[3] = "\"world\"";
	command[4] = "> output.txt >> log.txt < input.txt";
	command[5] = 0;
	//command = quotes_splitting(command, line);
	command = space_splitting(command);
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
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
		free(line);
	}
}
int	main(void)
{
	launch_shell();
	return (0);
}