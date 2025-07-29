/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:06:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 23:00:57 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	len_until_space_forward(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (i);
		i++;
	}
	return (i);
}

size_t	len_until_space_backward(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
		i++;
	while (i > 0)
	{
		if (ft_isspace(str[i - 1]))
			return (count);
		count++;
		i--;
	}
	return (count);
}

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

// Check if we should merge with previous token
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

int	call_join_next_prev(char ***command, char ***cmd, size_t *i, int *merged)
{
	int	returned_value;

	returned_value = 0;
	if (should_merge_prev(*command, *i))
	{
		if (is_quote((*command)[*i - 1][ft_strlen((*command)[*i - 1]) - 1]))
		{
			if (call_prev_quotes(command, cmd, i, merged))
				return (1);
		}
		else
		{
			if (call_prev_simple(command, cmd, i, merged) == 1)
				return (1);
		}
		print_cmd(*command);
		return (0);
	}
	returned_value = check_if_merge_needed(command, cmd, i, merged);
	if (returned_value == 0 || returned_value == 1)
		return (returned_value);
	return (0);
}

int	loop_in_continuous(char ***cmd, char ***command, int *changes_made)
{
	size_t	i;
	int		merged;

	i = 0;
	while ((*command)[i])
	{
		merged = 0;
		if (is_quote((*command)[i][0]))
		{
			if (call_join_next_prev(command, cmd, &i, &merged) == 1)
				return (1);
			*command = *cmd;
			if (merged)
			{
				*changes_made = 1;
				continue ;
			}
		}
		i++;
	}
	return (0);
}

int	contiguous_quotes(char ***cmd)
{
	size_t	i;
	char	**command;
	int		changes_made;

	changes_made = 1;
	while (changes_made)
	{
		changes_made = 0;
		i = 0;
		command = *cmd;
		if (loop_in_continuous(cmd, &command, &changes_made) == 1)
			return (1);
	}
	return (0);
}
