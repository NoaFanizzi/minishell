/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:01 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 02:27:38 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_space_count(char **command, const char *charset)
{
	int		count;
	size_t	i;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (command[i][0] == D_QUOTE || command[i][0] == S_QUOTE)
			count++;
		else
			count += count_words(command[i], charset);
		i++;
	}
	return (count);
}

char	**fill_space_words(char **splitted, char **command, const char *charset)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (command[k])
	{
		if (command[k][0] == D_QUOTE || command[k][0] == S_QUOTE)
		{
			splitted[i] = ft_substr(command[k], 0, ft_strlen(command[k]));
			if (!splitted[i])
				return (free_words(splitted));
			i++;
		}
		else
		{
			if (!fill_splitted(command[k], charset, splitted, &i))
				return (NULL);
		}
		k++;
	}
	splitted[i] = 0;
	return (splitted);
}

char	**space_splitting(char **command)
{
	int			count;
	char		**splitted;
	const char	charset[7] = {' ', '\n', '\t', '\f', '\v', '\r', 0};

	count = split_space_count(command, charset);
	splitted = malloc((count + 1) * sizeof(char *));
	if (!splitted)
		return (free_words(command));
	splitted = fill_space_words(splitted, command, charset);
	free_words(command);
	if (!splitted)
		return (NULL);
	return (splitted);
}
