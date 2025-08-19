/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:46:20 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/19 18:32:00 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_meta_count(char **command, const char *charset)
{
	int		count;
	size_t	i;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (command[i][0] == D_QUOTE || command[i][0] == S_QUOTE)
			count++;
		else
			count += twisted_count_words(command[i], charset);
		i++;
	}
	return (count);
}

size_t	find_next_segment(const char *s, const char *charset,
		size_t start)
{
	size_t	i;

	i = start;
	if (is_sep(s[i], charset))
	{
		while (s[i] && is_sep(s[i], charset))
		{
			if (s[i + 1] && is_sep(s[i + 1], charset) && s[i] != s[i + 1])
				break ;
			i++;
		}
	}
	else
	{
		while (s[i] && !is_sep(s[i], charset))
			i++;
	}
	return (i);
}

char	**twisted_fill_splitted(const char *s, const char *charset,
		char **splitted, size_t *j)
{
	int	tab[2];

	tab[0] = 0;
	tab[1] = 0;
	while (s[tab[0]])
	{
		tab[0] = tab[1];
		tab[1] = find_next_segment(s, charset, tab[1]);
		if (add_segment(s, &splitted, j, tab) == 1)
			return (free_words(splitted));
		if (!splitted)
			return (NULL);
	}
	return (splitted);
}

char	**fill_meta_words(char **splitted, char **command, const char *charset)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (command[k])
	{
		if (command[k][0] == D_QUOTE || command[k][0] == S_QUOTE)
		{
			splitted[i] = ft_strdup(command[k]);//PROTECTED
			if (!splitted[i])
				return (free_words(splitted));
			i++;
		}
		else
		{
			if (!twisted_fill_splitted(command[k], charset, splitted, &i))
				return (NULL);
		}
		k++;
	}
	splitted[i] = 0;
	return (splitted);
}

char	**meta_splitting(char **command)
{
	char		**splitted;
	int			count;
	const char	charset[4] = {'>', '<', '|', 0};

	count = split_meta_count(command, charset);
	splitted = malloc((count + 1) * sizeof(char *));//PROTECTED
	if (!splitted)
	{
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (free_words(command));
	}
	splitted = fill_meta_words(splitted, command, charset);
	free_words(command);
	if (!splitted)
	{
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (NULL);
	}
	return (splitted);
}
