/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_next_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:10:40 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 21:16:56 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	joined[k] = malloc(size * sizeof(char)); //PROTECTED
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
	return(0);
}

int	go_through_join_next_quotes(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (command[j])
	{
		joined[k] = 0;
		if (i == j)
		{
			if(fusion_quotes_next(command, joined, i, j + 1) == 1)
				return(1);
			j++;
		}
		else
			joined[k] = ft_strdup(command[j]); //PROTECTED
		if (!joined[k])
		{
			ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
			free_words(joined);
			joined = NULL;
			return (1);
		}
		j++;
		k++;
		joined[k] = 0;
	}
	return(0);
}

char	**join_next_quotes(char ***command, size_t i)
{
	size_t	size;
	char	**joined;

	size = 0;
	while ((*command)[size])
		size++;
	joined = malloc((size + 1) * sizeof(char *)); //PROTECTED
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
