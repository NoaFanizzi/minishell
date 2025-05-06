/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:30:20 by nbodin            #+#    #+#             */
/*   Updated: 2025/05/06 08:40:54 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	rem_and_shift(char *command)
{
	size_t	end;
	size_t	i;
	size_t	j;

	end = ft_strlen(command) - 1;
	printf("end = %zu\n", end);
	i = 0;
	j = 1;
	while (command[j])
	{
		if (!command[j + 1])
			break;
		command[i] = command[j];
		i++;
		j++;
	}
	command[i] = 0;
}

void	quotes_removal(char **command)
{
	size_t	k;

	k = 0;
	while (command[k])
	{
		if (command[k][0] == D_QUOTE || command[k][0] == S_QUOTE)
			rem_and_shift(command[k]);
		k++;
	}
}