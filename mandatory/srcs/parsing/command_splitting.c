/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_splitting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:46:29 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 08:49:01 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***init_splitted(char ***splitted, char **command)
{
	int		cmd_count;
	int		cmd_words_count;
	size_t	cmd_index;
	size_t	k;

	k = 0;
	cmd_index = 0;
	cmd_count = count_commands(command);
	//printf("cmd_count = %d\n", cmd_count);
	splitted = malloc((cmd_count + 1) * sizeof(char **));
	if (!splitted)
		return (NULL);
	while ((int)k < cmd_count)
	{
		cmd_words_count = count_command_words(&command[cmd_index]);
		cmd_index += cmd_words_count;
		splitted[k] = ft_calloc((cmd_words_count + 1), sizeof(char *));
		if (!splitted[k])
			return (free_command(splitted));
		k++;
	}
	splitted[k] = 0;
	return (splitted);
}

char	***fill_splitted_command(char ***splitted, char **command)
{
	size_t	k;
	size_t	i;
	size_t	cmd_index;
	int		cmd_count;
	int		cmd_words_count;

	cmd_index = 0;
	cmd_count = count_commands(command);
	k = -1;
	while ((int)++k < cmd_count)
	{
		cmd_words_count = count_command_words(&command[cmd_index]);
		i = -1;
		while ((int)++i < cmd_words_count)
		{
			splitted[k][i] = ft_strdup(command[cmd_index + i]);
			if (!splitted[k][i])
				return (free_command(splitted));
		}
		cmd_index += cmd_words_count;
		splitted[k][i] = 0;
	}
	splitted[k] = 0;
	return (splitted);
}

char	***command_splitting(char **command)
{
	char	***splitted;

	splitted = NULL;
	splitted = init_splitted(splitted, command);
	if (!splitted)
		return (NULL);
	splitted = fill_splitted_command(splitted, command);
	if (!splitted)
		return (NULL);
	return (splitted);
}
