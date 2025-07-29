/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_prev_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:13:20 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 02:26:55 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fusion_simple_prev(char **command, char **joined, size_t i, size_t j)
{
	size_t	size;
	size_t	k;

	k = 0;
	while (joined[k])
		k++;
	rem_and_shift(command[i]);
	size = len_until_space_backward(command[j]) + ft_strlen(command[i]) + 3;
	if (len_until_space_backward(command[j]) != ft_strlen(command[j]))
	{
		joined[k] = ft_substr(command[j], 0, ft_strlen(command[j])
				- len_until_space_backward(command[j]));
		if (!joined[k++])
			return ;
	}
	joined[k] = malloc(size * sizeof(char));
	if (!joined[k])
		return ;
	joined[k][0] = D_QUOTE;
	joined[k][1] = 0;
	ft_strlcat(joined[k], &command[j][ft_strlen(command[j])
		- len_until_space_backward(command[j])], size);
	ft_strlcat(joined[k], command[i], size);
	joined[k][size - 2] = D_QUOTE;
	joined[k][size - 1] = 0;
}

void	go_through_join_prev_simple(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = -1;
	k = 0;
	while (command[++j])
	{
		if (i - 1 == j)
		{
			fusion_simple_prev(command, joined, i, j);
			if (len_until_space_backward(command[j]) != ft_strlen(command[j]))
				k++;
			j++;
		}
		else
			joined[k] = ft_strdup(command[j]);
		if (check_free_joined(&joined, &k))
			return ;
		joined[k] = 0;
	}
}

char	**join_prev_simple(char **command, size_t i)
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
	go_through_join_prev_simple(command, joined, i);
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	free_words(command);
	return (joined);
}
