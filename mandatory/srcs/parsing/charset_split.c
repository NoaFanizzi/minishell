/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charset_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:19:13 by nbodin            #+#    #+#             */
/*   Updated: 2025/05/06 08:40:30 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		is_sep(char c, const char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		count_words(const char *str, const char *charset)
{
	int	count;
	size_t	i;
	int		is_word;

	is_word = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (!is_sep(str[i], charset) && is_word == 0)
		{
			count++;
			is_word = 1;
		}
		if (is_sep(str[i], charset))
			is_word = 0;
		i++;
	}
	return (count);
}

void	*free_words(char **splitted)
{
	size_t	j;

	j = 0;
	while (splitted[j])
	{
		free(splitted[j]);
		j++;
	}
	//free(splitted);
	return (NULL);
}

char	**fill_splitted(const char *s, const char *charset,
		char **splitted, size_t *j)
{
	size_t	i1;
	size_t	i2;

	i1 = 0;
	while (s[i1])
	{
		while (s[i1] && is_sep(s[i1], charset))
			i1++;
		i2 = i1;
		while (s[i2] && !is_sep(s[i2], charset))
			i2++;
		if (i2 > i1)
		{
			splitted[*j] = ft_substr(s, i1, i2 - i1);
			if (!splitted[*j])
				return (free_words(splitted));
			(*j)++;
		}
		i1 = i2;
	}
	return (splitted);
}
