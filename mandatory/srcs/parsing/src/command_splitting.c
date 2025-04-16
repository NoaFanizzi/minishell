/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_splitting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:46:29 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/16 17:41:13 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int		count_commands(char **command)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (command[i][0] == '|')
			count++;
		i++;
	}
	return (count + 1);
}

int		count_command_words(char **command)
{
	size_t	i;
	int	count;

	i = 0;
	count = 0;
	if (command[i][0] == '|')
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

void	init_splitted(char ***splitted, char **command)
{
	int		cmd_count;
	int		cmd_words_count;
	size_t	cmd_index;
	size_t	k;

	k = 0;
	cmd_index = 0;
	cmd_count = count_commands(command);
	splitted = malloc((cmd_count + 1) * sizeof(char **));
	if (!splitted)
		return ;//malloc error
	splitted[cmd_count] = 0;
	while ((int)k < cmd_count)
	{
		cmd_words_count = count_command_words(&command[cmd_index]);
		printf("command n%zu : %d words\n", k + 1, cmd_words_count);
		cmd_index += cmd_words_count;
		splitted[k] = malloc((cmd_words_count + 1) * sizeof(char *));
		if (!splitted[k])
			return ;//malloc error
		k++;
	}
}

char	***command_splitting(char **command)
{
	char	 ***splitted = NULL;
	
	init_splitted(splitted, command);
	if (!splitted)
		return (NULL);
	return (splitted);
}