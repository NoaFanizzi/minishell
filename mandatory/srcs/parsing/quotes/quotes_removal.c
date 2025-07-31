/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:30:20 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/31 17:59:41 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rem_and_shift(char *command)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	if (!command || ((command[0] != D_QUOTE || command[ft_strlen(command) - 1] != D_QUOTE)
		&& (command[0] != S_QUOTE || command[ft_strlen(command)
				- 1] != S_QUOTE)))
		return ;
	while (command[j])
	{
		if (!command[j + 1])
			break ;
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
		rem_and_shift(command[k]);
		k++;
	}
}
