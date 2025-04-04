/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/04 15:03:32 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	parse_command(char *line)
{	
	char 	**command = NULL;	

	quotes_sep(command, line);
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