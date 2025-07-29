/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_splitting_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:42:39 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 02:29:25 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(char **command)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (!command[i + 1] && command[i][0] == '|')
		{
			count++;
			return (count + count);
		}
		else if (command[i][0] == '|')
			count++;
		i++;
	}
	return (count + count + 1);
}

int	count_command_words(char **command)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	if (command[i] && command[i][0] == '|')
		return (1);
	while (command[i])
	{
		if (command[i][0] == '|')
			return (count);
		i++;
		count++;
	}
	return (count);
}

void	*free_command(char ***splitted)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!splitted)
		return (NULL);
	while ((splitted)[i])
	{
		j = 0;
		while ((splitted)[i][j])
		{
			free((splitted)[i][j]);
			j++;
		}
		free((splitted)[i]);
		i++;
	}
	free(splitted);
	splitted = NULL;
	return (NULL);
}
