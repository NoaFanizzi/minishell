/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_splitting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/07/29 19:59:25 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	split_quote_count(char *line)
{
	size_t	i;
	size_t	j;
	int		count;
	char	quote;

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

char	**fill_quote_words(char **command, char *line, size_t	k, size_t *i)
{
	char	quote;
	size_t	j;

	j = 0;
	if (line[*i] == D_QUOTE || line[*i] == S_QUOTE)
	{
		quote = line[*i];
		forward_till_quote(&line[*i], &j, quote);
		command[k] = ft_substr(line, *i, j + 1); //PROTECTED
		if (!command[k])
		{
			ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
			return (NULL);
		}
		*i += j + 1;
	}
	else
	{
		j = *i;
		while (line[j] && line[j] != D_QUOTE && line[j] != S_QUOTE)
			j++;
		command[k] = ft_substr(line, *i, j - *i); //PROTECTED
		if (!command[k])
		{
			ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
			return (NULL);
		}
		*i = j;
	}
	return (command);
}

char	**quotes_splitting(char **command, char *line)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	command = malloc((split_quote_count(line) + 1) * sizeof(char *)); //PROTECTED
	if (!command)
	{
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (NULL);
	}
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
