/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_prev_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:13:20 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/19 17:34:36 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_final_string(char **command, char **joined, size_t *sk,
		size_t ij[2])
{
	joined[sk[1]] = malloc(sk[0] * sizeof(char));//PROTECTED
	if (!joined[sk[1]])
		return (ft_putendl_fd("maxishell: malloc error", STDERR_FILENO), 1);
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

int	handle_prev_join_special(char **command, char ***joined,
				size_t i, size_t jk[2])
{
	if (fusion_simple_prev(command, *joined, i, jk[0]) == 1)
	{
		free_words(*joined);
		*joined = NULL;
		return (1);
	}
	if (len_until_space_backward(command[jk[0]])
		!= ft_strlen(command[jk[0]]))
		jk[1]++;
	return (0);
}

void	go_through_join_prev_simple(char **command, char ***joined, size_t i)
{
	size_t	jk[2];

	jk[0] = (size_t)-1;
	jk[1] = 0;
	while (command[++jk[0]])
	{
		if (i - 1 == jk[0])
		{
			if (handle_prev_join_special(command, joined, i, jk) == 1)
				return ;
			jk[0]++;
		}
		else
			(*joined)[jk[1]] = ft_strdup(command[jk[0]]);//PROTECTED
		if (!(*joined)[jk[1]])
		{
			ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
			free_words(*joined);
			*joined = NULL;
			return ;
		}
		jk[1]++;
		(*joined)[jk[1]] = NULL;
	}
	
}

char	**join_prev_simple(char ***command, size_t i)
{
	size_t	size;
	char	**joined;

	size = 0;
	while ((*command)[size])
		size++;
	joined = malloc((size + 1) * sizeof(char *));//PROTECTED
	if (!joined)
	{
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		free_words(*command);
		return (NULL);
	}
	joined[0] = 0;
	go_through_join_prev_simple(*command, &joined, i);
	if (!joined)
	{
		free_words(*command);
		return (NULL);
	}
	free_words(*command);
	return (joined);
}
