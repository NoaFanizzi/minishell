/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:46:20 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/10 17:56:53 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	twisted_count_words(char *str, const char *charset)
{
	int		count;
	size_t	i;
	
	i = 0; 
	count = 0;
	while (str[i])
	{
		if (is_sep(str[i], charset))
		{
			while (str[i] && is_sep(str[i], charset))
				i++;
			count++;
		}
		else
		{
			while (str[i] && !is_sep(str[i], charset))
				i++;
			count++;
		}
	}
	return (count);
}

int	split_meta_count(char **command, const char *charset)
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
			count += twisted_count_words(command[i], charset);
		i++;
	}
	printf("count = %d\n", count);
	return (count);
}

char	**fill_meta_words(char **splitted, char **command, const char *charset)
{
	
	
}

char	**meta_splitting(char **command)
{
	char	**splitted;
	int		count;
	const	char	charset[3] = {'>', '<', '|'};

	count = split_meta_count(command, charset);
	splitted = malloc((count + 1) * sizeof(char *));
	if (!splitted)
		return (free_words(command, ft_strlen(*command)));
	//splitted = fill_meta_words(splitted, command, charset);
	free_words(command, ft_strlen(*command));
	if (!splitted)
		return (NULL);
	return (splitted);
}