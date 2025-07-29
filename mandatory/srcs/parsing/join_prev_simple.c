/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_prev_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:13:20 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/30 00:05:14 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_space_case(char **command, char **joined, size_t *sk, size_t j)
{
	joined[sk[1]] = ft_substr(command[j], 0, ft_strlen(command[j])
			- len_until_space_backward(command[j]));
	if (!joined[sk[1]++])
		return (ft_putendl_fd("maxishell: malloc error", STDERR_FILENO), 1);
	return (0);
}

static int	create_final_string(char **command, char **joined, size_t *sk,
	size_t ij[2])
{
	joined[sk[1]] = malloc(sk[0] * sizeof(char));
	if (!joined[sk[1]])
	{
		free(joined[sk[1] - 1]);
		joined[sk[1]] = NULL;
		return (ft_putendl_fd("maxishell: malloc error", STDERR_FILENO), 1);
	}
	joined[sk[1]][0] = D_QUOTE;
	joined[sk[1]][1] = 0;
	ft_strlcat(joined[sk[1]], &command[ij[1]][ft_strlen(command[ij[1]])
		- len_until_space_backward(command[ij[1]])], sk[0]);
	ft_strlcat(joined[sk[1]], command[ij[0]], sk[0]);
	joined[sk[1]][sk[0] - 2] = D_QUOTE;
	joined[sk[1]][sk[0] - 1] = 0;
	return (0);
}

int	fusion_simple_prev(char **command, char **joined, size_t i, size_t j)
{
	size_t	sk[2];
	size_t	ij[2];

	ij[0] = i;
	ij[1] = j;
	sk[1] = 0;
	while (joined[sk[1]])
		sk[1]++;
	rem_and_shift(command[i]);
	sk[0] = len_until_space_backward(command[j]) + ft_strlen(command[i]) + 3;
	if (len_until_space_backward(command[j]) != ft_strlen(command[j]))
		if (handle_space_case(command, joined, sk, j))
			return (1);
	if (create_final_string(command, joined, sk, ij))
		return (1);
	return (0);
}

int	go_through_join_prev_simple(char **command, char **joined, size_t i)
{
	size_t	jk[2];

	jk[0] = -1;
	jk[1] = 0;
	while (command[++jk[0]])
	{
		if (i - 1 == jk[0])
		{
			if (fusion_simple_prev(command, joined, i, jk[0]) == 1)
				return (1);
			if (len_until_space_backward(command[jk[0]]) != ft_strlen(command[jk[0]]))
				jk[1]++;
			jk[0]++;
		}
		else
		{
			joined[jk[1]] = ft_strdup(command[jk[0]]);
			if (!joined[jk[1]])
				return (ft_putendl_fd("maxishell: malloc error", STDERR_FILENO), 1);
		}
		if (check_free_joined(&joined, &jk[1]))
			return (1);
		joined[jk[1]] = 0;
	}
	return (0);
}

char	**join_prev_simple(char ***command, size_t i)
{
	size_t	size;
	char	**joined;

	size = 0;
	while ((*command)[size])
		size++;
	joined = malloc((size + 1) * sizeof(char *)); // PROTECTED
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
