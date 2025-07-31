/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_quotes_helpers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:07:30 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/31 20:05:02 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	call_prev_quotes(char ***command, char ***cmd, size_t *i, int *merged)
{
	*command = join_prev_quotes(command, *i);
	if (!*command)
		return (1);
	*cmd = *command;
	(*i)--;
	*merged = 1;
	return (0);
}

int	call_prev_simple(char ***command, char ***cmd, size_t *i, int *merged)
{
	*command = join_prev_simple(command, *i);
	if (!*command)
		return (1);
	*cmd = *command;
	(*i)--;
	*merged = 1;
	return (0);
}

int	call_next_quotes(char ***command, char ***cmd, size_t i, int *merged)
{
	*command = join_next_quotes(command, i);
	if (!*command)
		return (1);
	*cmd = *command;
	*merged = 1;
	return (0);
}

int	call_next_simple(char ***command, char ***cmd, size_t *i, int *merged)
{
	printf("here\n");
	printf("i = %zu, *cmd[i] = %s\n",*i, (*command)[*i]);
	int k = 0;
	while ((*command)[k])  // ← FIXED: Use *command instead of command
	{
		printf("word n%d : %s\n", k, (*command)[k]);  // ← SIMPLIFIED: just print the word
		k++;
	}
	*command = join_next_simple(command, *i);
	if (!*command)
		return (1);
	*cmd = *command;
	*merged = 1;
	(*i)++;
	printf("I = %zu, *cmd[i] = %s\n",*i, (*command)[*i]);
	k = 0;
	while ((*command)[k])  // ← FIXED: Use *command instead of command
	{
		printf("word n%d : %s\n", k, (*command)[k]);  // ← SIMPLIFIED: just print the word
		k++;
	}
	return (0);
}

int	call_join_prev(char ***command, char ***cmd, size_t *i, int *merged)
{
	if (*i > 0 && (*command)[*i - 1] && ft_strlen((*command)[*i - 1]) > 0
		&& is_quote((*command)[*i - 1][ft_strlen((*command)[*i - 1]) - 1]))
	{
		if (call_prev_quotes(command, cmd, i, merged))
			return (1);
	}
	else if (*i > 0 && (*command)[*i - 1] && ft_strlen((*command)[*i - 1]) > 0
		&& (ft_isspace((*command)[*i - 1][ft_strlen((*command)[*i - 1])
				- 1]) == 0) && is_not_pipe_redir((*command)[*i
			- 1][ft_strlen((*command)[*i - 1]) - 1]))
	{
		if (call_prev_simple(command, cmd, i, merged))
			return (1);
	}
	return (0);
}
