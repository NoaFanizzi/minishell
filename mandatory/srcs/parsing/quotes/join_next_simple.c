/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_next_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:11:27 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/03 14:45:47 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alloc_and_prepare_joined(char **command, char **joined,
		size_t idx[3])
{
	size_t	size;
	size_t   first_len;

	idx[2] = 0;
	while (joined[idx[2]])
		idx[2]++;
	rem_and_shift(command[idx[0]]);
	first_len = len_until_space_forward(command[idx[1]]);
	size = first_len + ft_strlen(command[idx[0]]) + 3;
	joined[idx[2]] = malloc(size * sizeof(char));
	if (!joined[idx[2]])
	{
		joined[idx[2]] = NULL;
		return (1);
	}
	joined[idx[2]][0] = D_QUOTE;
	joined[idx[2]][1] = 0;
	// Add the current token
	ft_strlcat(joined[idx[2]], command[idx[0]], size);
	// Add only the first segment of the next token
	strncat(joined[idx[2]], command[idx[1]], first_len);
	joined[idx[2]][size - 2] = D_QUOTE;
	joined[idx[2]][size - 1] = 0;
	return (0);
}

int	fusion_simple_next(char **command, char **joined, size_t idx[3])
{
	size_t first_len;

	if (alloc_and_prepare_joined(command, joined, idx) == 1)
		return (1);

	first_len = len_until_space_forward(command[idx[1]]);
	if (first_len != ft_strlen(command[idx[1]]))
	{
		// Keep everything starting from first_len (including the spaces!)
		joined[idx[2] + 1] = ft_strdup(&command[idx[1]][first_len]);
		if (!joined[idx[2] + 1])
			return (1);
	}
	return (0);
}


int	manage_next_simple(char **command, char ***joined, size_t idx[3])
{
	size_t	fusion_idx[3];

	fusion_idx[0] = idx[0];
	fusion_idx[1] = idx[1] + 1;
	fusion_idx[2] = idx[2];
	if (fusion_simple_next(command, *joined, fusion_idx) == 1)
	{
		ft_free_tab_length(*joined, idx[0]);
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (1);
	}
	if (len_until_space_forward(command[idx[1] + 1]) != ft_strlen(command[idx[1]
				+ 1]))
	{
		if (check_free_joined(joined, &idx[2]))
			return (1);
	}
	idx[1] += 1;
	return (0);
}

int	go_through_join_next_simple(char **command, char **joined, size_t i)
{
	size_t	idx[3];

	idx[0] = i;
	idx[1] = 0;
	idx[2] = 0;
	while (command[idx[1]])
	{
		if (idx[0] == idx[1])
		{
			if (manage_next_simple(command, &joined, idx) == 1)
				return (1);
		}
		else
		{
			joined[idx[2]] = ft_strdup(command[idx[1]]);
		}
		if (check_free_joined(&joined, &idx[2]))
			return (1);
		joined[idx[2]] = 0;
		idx[1]++;
	}
	return (0);
}

char	**join_next_simple(char ***command, size_t i)
{
	size_t	size;
	char	**joined;

	size = 0;
	while ((*command)[size])
		size++;
	joined = malloc((size + 1) * sizeof(char *));
	if (!joined)
	{
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		free_words(*command);
		return (NULL);
	}
	joined[0] = 0;
	if (go_through_join_next_simple(*command, joined, i) == 1 || !joined)
	{
		free_words(*command);
		return (NULL);
	}
	free_words(*command);
	return (joined);
}
