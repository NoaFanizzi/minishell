/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_splitting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:13:01 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/09 17:05:32 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

//NEED TO DO THE FREES
//NEED TO FIND A WAY FOR THE NORMINETTE OTHER THAN STATIC STRUCTURE

int	split_quote_count(char *line)
{
	size_t		i;
	size_t		j;
	int					count;
	char				quote;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != D_QUOTE && line[i] != S_QUOTE)
		{
			j = i;
			while (line[j] && line[j] != D_QUOTE && line[j] != S_QUOTE)
				j++;
			if (j > i)
				count++;
			i = j;
		}
		else
		{
			quote = line[i];
			forward_till_quote(&line[i], &j, quote);
			count++;
			i += j + 1;
		}
	}
	printf("count = %d\n", count);//to remove
	return (count);
}

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
				return (1);
			i += j + 1;
		}
		else
			i++;
	}
	return (0);
}

void	fill_quote_words(char **command, char *line, t_index_q *index)
{
	char	quote;

	if (line[index->i] == D_QUOTE || line[index->i] == S_QUOTE)
	{
		quote = line[index->i];
		forward_till_quote(&line[index->i], &index->j, quote);
		command[index->k] = ft_substr(line, index->i, index->j + 1);
		if (!command[index->k])
			return ; // malloc error
		index->i += index->j + 1;
		index->k++;
	}
	else
	{
		index->j = index->i;
		while (line[index->j] && line[index->j] != D_QUOTE
			&& line[index->j] != S_QUOTE)
			index->j++;
		command[index->k] = ft_substr(line, index->i, index->j - index->i);
		if (!command[index->k])
			return ; // malloc error
		index->i = index->j;
		index->k++;
	}
}

char	**quotes_splitting(char **command, char *line)
{
	t_index_q	*index;

	index = malloc(sizeof(*index));
	if (!index)
		return (NULL);
	index->i = 0;
	index->j = 0;
	index->k = 0;
	if (quotes_checker(line) == 1)
		return (NULL); // quote_error
	command = malloc((split_quote_count(line) + 1) * sizeof(char *));
	if (!command)
		return (NULL); // malloc error
	while (line[index->i])
	{
		fill_quote_words(command, line, index);
		if (!command[index->k - 1])
			return (NULL);
	}
	command[index->k] = 0;
	return (command);
}
