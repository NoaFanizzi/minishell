/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_next_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:10:40 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/20 15:40:44 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_space_case(char **command, char **joined, size_t *sk,
		size_t j)
{
	(void)j;
	(void) command;
	joined[sk[1]] = ft_substr(command[j], 0, ft_strlen(command[j])
			- len_until_space_backward(command[j]));
	if (!joined[sk[1]++])
		return (ft_putendl_fd("maxishell: malloc error", STDERR_FILENO), 1);
	return (0);
}

int	fusion_quotes_next(char **command, char **joined, size_t i, size_t j)
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
	{
		ft_free_tab_length(joined, k);
		joined = NULL;
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (1);
	}
	joined[k][0] = D_QUOTE;
	joined[k][1] = 0;
	ft_strlcat(joined[k], command[i], size);
	ft_strlcat(joined[k], command[j], size);
	joined[k][size - 2] = D_QUOTE;
	joined[k][size - 1] = 0;
	return (0);
}

int	go_through_join_next_quotes(char **command, char **joined, size_t i)
{
	size_t	idx[2];

	idx[0] = (size_t)-1;
	idx[1] = 0;
	while (command[++idx[0]])
	{
		joined[idx[1]] = NULL;
		if (i == idx[0])
		{
			if (fusion_quotes_next(command, joined, i, idx[0] + 1) == 1)
				return (1);
			idx[0]++;
		}
		else
			joined[idx[1]] = ft_strdup(command[idx[0]]);
		if (!joined[idx[1]])
		{
			ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
			free_words(joined);
			return (1);
		}
		idx[1]++;
		joined[idx[1]] = NULL;
	}
	return (0);
}

char	**join_next_quotes(char ***command, size_t i)
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
	if (go_through_join_next_quotes(*command, joined, i) == 1 || !joined)
	{
		free_words(*command);
		return (NULL);
	}
	free_words(*command);
	return (joined);
}
