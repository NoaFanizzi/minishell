/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:06:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/31 20:05:09 by nbodin           ###   ########lyon.fr   */
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

int	call_join_next_prev(char ***command, char ***cmd, size_t *i, int *merged)
{
	int	returned_value;

	returned_value = 0;
	printf("i value before merge needed = %zu\n", *i);
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
		return (0);
	}
	returned_value = check_if_merge_needed(command, cmd, i, merged);
	if (returned_value == 0 || returned_value == 1)
		return (returned_value);
	return (0);
}

int	loop_in_continuous(char ***cmd, char ***command, int *changes_made, size_t *i)
{
	int		merged;

	while ((*command)[*i])
	{
		merged = 0;
		printf("VALUE = %zu\n", *i);
		if (is_quote((*command)[*i][0]))
		{
			printf("Before call_join_next_prev: i = %zu\n", *i);
			if (call_join_next_prev(command, cmd, i, &merged) == 1)
				return (1);
			printf("After call_join_next_prev: i = %zu\n", *i);
			*command = *cmd;
			printf("After *command = *cmd: i = %zu\n", *i);
			if (merged)
			{
				*changes_made = 1;
				continue ;
			}
		}
		printf("BEFORE INCREMENT : %zu\n", *i);
		(*i)++;
		printf("AFTER INCREMENT : %zu\n", *i);
	}
	printf("EXITING\n");
	return (0);
}

int	contiguous_quotes(char ***cmd)
{
	size_t	i;
	char	**command;
	int		changes_made;

	changes_made = 1;
	i = 0;
	while (changes_made)
	{
		changes_made = 0;
		command = *cmd;
		if (loop_in_continuous(cmd, &command, &changes_made, &i) == 1)
			return (1);
	}
	return (0);
}
