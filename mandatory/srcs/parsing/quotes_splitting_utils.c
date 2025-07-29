/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_splitting_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:45:26 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 18:45:39 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	forward_till_quote(char *line, size_t *len, char quote)
{
	*len = 1;
	while (line[*len])
	{
		if (line[*len] == quote)
			return (0);
		(*len)++;
	}
	return (1);
}

void	skip_inside_quotes(size_t *i, size_t *j, char *line, int *count)
{
	*j = *i;
	while (line[*j] && line[*j] != D_QUOTE && line[*j] != S_QUOTE)
		(*j)++;
	if (*j > *i)
		(*count)++;
	*i = *j;
}

int	quotes_checker(char *line)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == D_QUOTE || line[i] == S_QUOTE)
		{
			quote = line[i];
			if (forward_till_quote(&line[i], &j, quote))
			{
				printf("maxishell: syntax error: unmatched quote\n");
				return (1);
			}
			i += j + 1;
		}
		else
			i++;
	}
	return (0);
}
