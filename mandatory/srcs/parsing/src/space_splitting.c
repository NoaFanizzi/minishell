/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:01 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/09 17:52:56 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int		split_space_count(char **command, const char *charset)
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
	printf("count = %d\n", count);
	return (count);
}

char	**fill_space_words(char **command, char **splitted, const char *charset)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (command[k])
	{
		if (command[k][0] == D_QUOTE || command[k][0] == S_QUOTE)//quoted
		{
			splitted[i] = ft_substr(command[k], 0, ft_strlen(command[k]));
			if (!splitted[i])
				return (NULL);
			printf("%s\n", splitted[i]);
			i++;
		}
		else
		{
			fill_splitted(command[k], charset, splitted, &i);
			//i do not check if NULL for now
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
	
	const char	charset[3] = {' ', '\n', '\t'};
	count = split_space_count(command, charset);
	splitted = malloc((count + 1) * sizeof(char *));
	if (!splitted)
		return (NULL);
	splitted = fill_space_words(splitted, command, charset);
	if (!splitted)
		return (NULL);
	return (splitted);
}
