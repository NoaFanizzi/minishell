/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_next_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:10:40 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 02:20:32 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fusion_quotes_next(char **command, char **joined, size_t i, size_t j)
{
	size_t	size;
	size_t	k;

	k = 0;
	while (joined[k])
		k++;
	rem_and_shift(command[j]);
	rem_and_shift(command[i]);
	size = ft_strlen(command[j]) + ft_strlen(command[i]) + 3;
	joined[k] = malloc(size * sizeof(char));
	if (!joined[k])
		return ;
	joined[k][0] = D_QUOTE;
	joined[k][1] = 0;
	ft_strlcat(joined[k], command[i], size);
	ft_strlcat(joined[k], command[j], size);
	joined[k][size - 2] = D_QUOTE;
	joined[k][size - 1] = 0;
}

void	go_through_join_next_quotes(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (command[j])
	{
		if (i == j)
		{
			fusion_quotes_next(command, joined, i, j + 1);
			j++;
		}
		else
			joined[k] = ft_strdup(command[j]);
		if (!joined[k])
		{
			free_words(joined);
			joined = NULL;
			return ;
		}
		j++;
		k++;
		joined[k] = 0;
	}
}

char	**join_next_quotes(char **command, size_t i)
{
	size_t	size;
	char	**joined;

	size = 0;
	while (command[size])
		size++;
	joined = malloc((size + 1) * sizeof(char *));
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	joined[0] = 0;
	go_through_join_next_quotes(command, joined, i);
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	free_words(command);
	return (joined);
}
