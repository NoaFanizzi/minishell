/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_quotes_merging.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:44:42 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/03 14:51:23 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	are_contiguous(char *prev, char *curr)
{
	size_t	prev_len;

	if (!prev || !curr)
		return (0);
	prev_len = ft_strlen(prev);
	if (prev_len == 0)
		return (0);
	return (!ft_isspace(prev[prev_len - 1]) && !ft_isspace(curr[0]));
}

int	should_merge_prev(char **command, size_t i)
{
	size_t	prev_len;

	if (i == 0 || !command[i - 1])
		return (0);
	if (!are_contiguous(command[i - 1], command[i]))
		return (0);
	prev_len = ft_strlen(command[i - 1]);
	if (prev_len == 0)
		return (0);
	return (is_quote(command[i - 1][prev_len - 1])
		|| is_not_pipe_redir(command[i - 1][prev_len - 1]));
}

int	should_merge_next(char **command, size_t i)
{
	if (!command[i + 1])
		return (0);
	if (!are_contiguous(command[i], command[i + 1]))
		return (0);
	return (is_quote(command[i + 1][0]) || (is_not_pipe_redir(command[i + 1][0])
			&& !ft_isspace(command[i + 1][0])));
}

int	check_if_merge_needed(char ***command, char ***cmd, size_t *i, int *merged)
{
	if (should_merge_next(*command, *i))
	{
		if (is_quote((*command)[*i + 1][0]))
		{
			if (call_next_quotes(command, cmd, *i, merged))
				return (1);
		}
		else
		{
			if (call_next_simple(command, cmd, i, merged))
				return (1);
		}
		return (0);
	}
	return (2);
}
