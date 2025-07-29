/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:06:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 14:49:32 by nbodin           ###   ########lyon.fr   */
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

// Check if two tokens are truly contiguous (no spaces between them)
int	are_contiguous(char *prev, char *curr)
{
	size_t	prev_len;
	
	if (!prev || !curr)
		return (0);
	
	prev_len = ft_strlen(prev);
	if (prev_len == 0)
		return (0);
		
	// Check if previous token ends without space and current starts without space
	return (!ft_isspace(prev[prev_len - 1]) && !ft_isspace(curr[0]));
}

// Check if we should merge with previous token
int	should_merge_prev(char **command, size_t i)
{
	if (i == 0 || !command[i - 1])
		return (0);
		
	if (!are_contiguous(command[i - 1], command[i]))
		return (0);
		
	size_t prev_len = ft_strlen(command[i - 1]);
	if (prev_len == 0)
		return (0);
		
	// Check if previous ends with quote or is not a pipe/redirect
	return (is_quote(command[i - 1][prev_len - 1]) || 
			is_not_pipe_redir(command[i - 1][prev_len - 1]));
}

// Check if we should merge with next token
int	should_merge_next(char **command, size_t i)
{
	if (!command[i + 1])
		return (0);
		
	if (!are_contiguous(command[i], command[i + 1]))
		return (0);
		
	// Check if next starts with quote or is not a pipe/redirect
	return (is_quote(command[i + 1][0]) || 
			(is_not_pipe_redir(command[i + 1][0]) && !ft_isspace(command[i + 1][0])));
}

int	call_join_next_prev(char ***command, char ***cmd, size_t *i, int *merged)
{
	// First try to merge with previous
	if (should_merge_prev(*command, *i))
	{
		if (is_quote((*command)[*i - 1][ft_strlen((*command)[*i - 1]) - 1]))
		{
			printf("command[i-1] = %s\n", (*command)[*i - 1]);
			if (call_prev_quotes(command, cmd, i, merged))
				return (1);
		}
		else
		{
			printf("command[i-1] = %s\n", (*command)[*i - 1]);
			if (call_prev_simple(command, cmd, i, merged))
				return (1);
		}
		print_cmd(*command);
		return (0);
	}
	
	// Then try to merge with next
	if (should_merge_next(*command, *i))
	{
		if (is_quote((*command)[*i + 1][0]))
		{
			printf("command[i+1] = %s\n", (*command)[*i + 1]);
			if (call_next_quotes(command, cmd, *i, merged))
				return (1);
		}
		else
		{
			printf("command[i+1] = %s\n", (*command)[*i + 1]);
			if (call_next_simple(command, cmd, i, merged))
				return (1);
		}
		print_cmd(*command);
		return (0);
	}
	
	return (0);
}

void	contiguous_quotes(char ***cmd)
{
	size_t	i;
	char	**command;
	int		merged;
	int		changes_made;

	do {
		changes_made = 0;
		i = 0;
		command = *cmd;
		
		while (command[i])
		{
			merged = 0;
			if (is_quote(command[i][0]))
			{
				if (call_join_next_prev(&command, cmd, &i, &merged))
					return;
				command = *cmd;
				if (merged)
				{
					changes_made = 1;
					// Don't increment i, recheck this position
					continue;
				}
			}
			i++;
		}
	} while (changes_made);
}
