/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_splitting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:13:01 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/28 22:16:48 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NEED TO DO THE FREES
//NEED TO FIND A WAY FOR THE NORMINETTE OTHER THAN STATIC STRUCTURE

void	skip_inside_quotes(size_t *i, size_t *j, char *line, int *count)
{
	*j = *i;
	while (line[*j] && line[*j] != D_QUOTE && line[*j] != S_QUOTE)
		(*j)++;
	if (*j > *i)
		(*count)++;
	*i = *j;
}

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
			skip_inside_quotes(&i, &j, line, &count);
		else
		{
			quote = line[i];
			forward_till_quote(&line[i], &j, quote);
			count++;
			i += j + 1;
		}
	}
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
			{
				printf("bash: syntax error: unmatched quote\n");
				return (1);
			}
			i += j + 1;
		}
		else
			i++;
	}
	return (0);
}

char	**fill_quote_words(char **command, char *line, size_t	k, size_t *i)
{
	char	quote;
	size_t	j;

	j = 0;
	if (line[*i] == D_QUOTE || line[*i] == S_QUOTE)
	{
		quote = line[*i];
		forward_till_quote(&line[*i], &j, quote);
		command[k] = ft_substr(line, *i, j + 1);
		if (!command[k])
			return (NULL);
		*i += j + 1;
	}
	else
	{
		j = *i;
		while (line[j] && line[j] != D_QUOTE
			&& line[j] != S_QUOTE)
			j++;
		command[k] = ft_substr(line, *i, j - *i);
		if (!command[k])
			return (NULL);
		*i = j;
	}
	return (command);
}

char	**quotes_splitting(char **command, char *line)
{
	size_t		i;
	size_t		k;

	i = 0;
	k = 0;
	command = malloc((split_quote_count(line) + 1) * sizeof(char *));
	if (!command)
		return (NULL); // malloc error
	while (line[i])
	{
		fill_quote_words(command, line, k, &i);
		if (!command[k])
			return (free_words(command));
		k++;
	}
	command[k] = 0;
	return (command);
}
