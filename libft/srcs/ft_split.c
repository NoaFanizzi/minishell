/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:39:20 by nofanizz          #+#    #+#             */
/*   Updated: 2024/11/12 11:09:27 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static size_t	ft_word_size(const char *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] == c)
	{
		i++;
		j++;
	}
	while (str[i] && (str[i] != c))
		i++;
	i++;
	return (i - j);
}

static int	ft_check_set(char c, char set)
{
	if (c == set)
		return (1);
	return (0);
}

static void	free_tab(char **str, int i)
{
	i--;
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	length;
	size_t	words;

	if (!s)
		return (NULL);
	i = -1;
	length = 0;
	words = ft_count_words(s, c);
	str = ft_calloc(words + 1, sizeof(char *));
	if (!str)
		return (NULL);
	while (++i < words)
	{
		str[i] = ft_calloc((ft_word_size((char *)&s[length], c)), sizeof(char));
		if (!str[i])
			return (free_tab(str, i), NULL);
		while (ft_check_set(s[length], c) == 1)
			length++;
		ft_strlcpy(str[i], (char *)&s[length],
			(unsigned int)(ft_word_size((char *)&s[length], c)));
		length = length + ft_word_size((char *)&s[length], c);
	}
	return (str);
}
