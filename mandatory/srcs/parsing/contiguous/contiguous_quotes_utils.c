/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_quotes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:05:52 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 02:18:21 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_not_pipe_redir(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (0);
	return (1);
}

int	is_quote(char c)
{
	if (c == S_QUOTE || c == D_QUOTE)
		return (1);
	return (0);
}

void	shift_words(char **command, size_t i)
{
	while (command[i + 1])
	{
		ft_strcpy(command[i], command[i + 1]);
		i++;
	}
	command[i] = 0;
}

int	check_free_joined(char ***joined, size_t *k)
{
	if (!(*joined)[*k])
	{
		free_words(*joined);
		*joined = NULL;
		return (1);
	}
	(*k)++;
	return (0);
}

int	ft_isspace(char c)
{
	if ((9 <= c && c <= 13) || (c == 32))
		return (1);
	return (0);
}
