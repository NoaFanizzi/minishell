/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_prev_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:09:02 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/30 01:46:19 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fusion_quotes_prev(char **command, char **joined, size_t i, size_t j)
{
	size_t	size;
	size_t	k;

	k = 0;
	while (joined[k])
		k++;
	rem_and_shift(command[i]);
	rem_and_shift(command[j]);
	size = ft_strlen(command[j]) + ft_strlen(command[i]) + 3;
	joined[k] = malloc(size * sizeof(char));
	if (!joined[k])
	{
		joined[k] = NULL;
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return ;
	}
	joined[k][0] = D_QUOTE;
	joined[k][1] = 0;
	ft_strlcat(joined[k], command[j], size);
	ft_strlcat(joined[k], command[i], size);
	joined[k][size - 2] = D_QUOTE;
	joined[k][size - 1] = 0;
}

void	go_through_join_prev_quotes(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (command[j])
	{
		if (i - 1 == j)
			fusion_quotes_prev(command, joined, i, j);
		else
			joined[k] = ft_strdup(command[j]);
		if (!joined[k])
		{
			ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
			free_words(joined);
			joined = NULL;
			return ;
		}
		if (i - 1 == j)
			j++;
		j++;
		k++;
		joined[k] = 0;
	}
}

char	**join_prev_quotes(char ***command, size_t i)
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
	go_through_join_prev_quotes(*command, joined, i);
	if (!joined)
	{
		free_words(*command);
		return (NULL);
	}
	free_words(*command);
	return (joined);
}
