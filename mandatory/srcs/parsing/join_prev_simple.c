/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_prev_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:13:20 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 20:49:20 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fusion_simple_prev(char **command, char **joined, size_t i, size_t j)
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
		joined[k] = ft_substr(command[j], 0, ft_strlen(command[j]) - len_until_space_backward(command[j])); //PROTECTED
		if (!joined[k++])
		{
			ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
			return (1);
		}
	}
	joined[k] = malloc(size * sizeof(char)); //PROTECTED
	if (!joined[k])
	{
		free(joined[k - 1]);
		joined[k] = NULL;
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (1);
	}
	joined[k][0] = D_QUOTE;
	joined[k][1] = 0;
	ft_strlcat(joined[k], &command[j][ft_strlen(command[j])
		- len_until_space_backward(command[j])], size);
	ft_strlcat(joined[k], command[i], size);
	joined[k][size - 2] = D_QUOTE;
	joined[k][size - 1] = 0;
	return(0);
}

int		go_through_join_prev_simple(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = -1;
	k = 0;
	while (command[++j])
	{
		if (i - 1 == j)
		{
			if(fusion_simple_prev(command, joined, i, j) == 1)
				return(1);
			if (len_until_space_backward(command[j]) != ft_strlen(command[j]))
				k++;
			j++;
		}
		else
		{
			joined[k] = ft_strdup(command[j]); //PROTECTED
			if(!joined[k])
			{
				ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
				return(1);
			}
		}
		if (check_free_joined(&joined, &k))
			return(1);
		joined[k] = 0;
	}
	return(0);
}

char	**join_prev_simple(char ***command, size_t i)
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
	if (go_through_join_prev_simple(*command, joined, i) == 1 || !joined)
	{
		free(joined);
		free_words(*command);
		return (NULL);
	}
	free_words(*command);
	return (joined);
}
