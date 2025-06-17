/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:30:20 by nbodin            #+#    #+#             */
/*   Updated: 2025/06/17 13:09:00 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rem_and_shift(char *command)
{
	size_t	i;
	size_t	j;

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
	command[i + 1] = 0;
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