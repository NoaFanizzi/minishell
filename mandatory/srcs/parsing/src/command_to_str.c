/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/02 10:41:25 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"




void	command_line_to_tab(void)
{
	char	*line;
	char	*full_command;

	line = get_next_line(1);
	full_command = ft_strjoin((const char*)full_command, (const char*)line);
	//printf("\n\n%s", line);
	while (line != NULL)
	{
		line = get_next_line(1);
		//printf("%s", line);
		full_command = ft_strjoin(full_command, line);
		printf("\n\n%s", full_command);
	}
}

int	main(void)
{
	//display_prompt();
	command_line_to_tab();
	return (0);
}