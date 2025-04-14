/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:30:20 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/14 10:53:59 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	rem_and_shift(char *command)
{
	size_t	end;

	end = ft_strlen(command) - 1;
	printf("end = %zu\n", end);
	
}

char	**quotes_removal(char **command)
{
	size_t	k;

	k = 0;
	while (command[k])
	{
		if (command[k][0] == D_QUOTE || command[k][0] == S_QUOTE)
			rem_and_shift(command[k]);
		k++;
	}
	return (command);
}