/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_next_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:11:27 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 02:19:35 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fusion_simple_next(char **command, char **joined, size_t i, size_t j)
{
	size_t	size;
	size_t	k;

	k = 0;
	while (joined[k])
		k++;
	rem_and_shift(command[i]);
	size = len_until_space_forward(command[j]) + ft_strlen(command[i]) + 3;
	joined[k] = malloc(size * sizeof(char));
	if (!joined[k])
		return ;
	joined[k][0] = D_QUOTE;
	joined[k][1] = 0;
	ft_strlcat(joined[k], command[i], size);
	ft_strlcat(joined[k], command[j], size);
	joined[k][size - 2] = D_QUOTE;
	joined[k][size - 1] = 0;
	if (len_until_space_forward(command[j]) != ft_strlen(command[j]))
		joined[k
			+ 1] = ft_strdup(&command[j][len_until_space_forward(command[j])
				+ 1]);
}

void	go_through_join_next_simple(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = -1;
	k = 0;
	while (command[++j])
	{
		if (i == j)
		{
			fusion_simple_next(command, joined, i, j + 1);
			if (len_until_space_forward(command[j + 1]) != ft_strlen(command[j
						+ 1]))
			{
				if (check_free_joined(&joined, &k))
					return ;
			}
			j++;
		}
		else
			joined[k] = ft_strdup(command[j]);
		if (check_free_joined(&joined, &k))
			return ;
		joined[k] = 0;
	}
}

char	**join_next_simple(char **command, size_t i)
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
	go_through_join_next_simple(command, joined, i);
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	free_words(command);
	return (joined);
}
