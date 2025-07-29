/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:06:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 08:50:27 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	call_join_next_prev(char **command, char ***cmd, size_t *i, int *merged)
{
	if (call_join_prev(command, cmd, i, merged))
		return (1);
	else if (command[*i + 1] && is_quote(command[*i + 1][0]))
	{
		if (call_next_quotes(command, cmd, *i, merged))
			return (1);
		return (0);
	}
	else if (command[*i + 1] && (ft_isspace(command[*i + 1][0]) == 0)
		&& is_not_pipe_redir(command[*i + 1][0]))
	{
		if (call_next_simple(command, cmd, i, merged))
			return (1);
	}
	return (0);
}

void	contiguous_quotes(char ***cmd)
{
	size_t	i;
	char	**command;
	int		merged;

	i = 0;
	command = *cmd;
	command = *cmd;
	while (command[i])
	{
		merged = 0;
		if (is_quote(command[i][0]))
		{
			if (call_join_next_prev(command, cmd, &i, &merged))
				return ;
			command = *cmd;
		}
		if (merged == 0)
			i++;
		else
			continue ;
	}
}
