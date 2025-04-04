/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:13:01 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/04 17:01:34 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"


//NEED TO CODE THE SPLIT_COUNT_QUOTE FUNCTION


int		forward_till_quote(char *line, size_t *len, int quote)
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

int		quotes_checker(char *line, int	*split_count)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == D_QUOTE || line[i] == S_QUOTE)
		{
			quote = line[i];
			split_count++;
			if (forward_till_quote(&line[i], &j, quote) == 1)
				return (1);
			if (i != 0)
				split_count++;
			i += j + 1;
		}
		else
			i++;
	}
	return (0);
}

void	quotes_sep(char **command, char *line)
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		quote;
	int		split_count;

	i = 0;
	j = 0;
	k = 0;
	split_count = 0;
	if (quotes_checker(line, &split_count) == 1)
		printf("quotes error\n");
	else
		printf("alright\n");
	command = malloc((quote_split_count(line) + 1) * sizeof(char *));
	if (!command)
		return ;//malloc error
	while (line[i])
	{
		if (line[i] == D_QUOTE || line[i] == S_QUOTE)
		{
			quote = line[i];
			forward_till_quote(&line[i], &j, quote);
			command[k] = malloc((j + 1) * sizeof(char));
			if (!command[k])
				return ;//malloc error
			command[k] = ft_substr(line, i, j);
			i += j + 1;
			k++;
		}
		else
			i++;
	}
}
