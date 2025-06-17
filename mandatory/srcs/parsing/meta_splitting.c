/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:46:20 by nbodin            #+#    #+#             */
/*   Updated: 2025/06/17 18:00:48 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	twisted_count_words(char *str, const char *charset)
{
	int		count;
	size_t	i;
	
	i = 0; 
	count = 0;
	while (str[i])
	{
		if (is_sep(str[i], charset))
		{
			while (str[i] && is_sep(str[i], charset))
			{
				i++;
				if (str[i] && is_sep(str[i], charset) && str[i - 1] != str[i])
					break ;
			}
			count++;
		}
		else
		{
			while (str[i] && !is_sep(str[i], charset))
				i++;
			count++;
		}
	}
	return (count);
}

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
	//("count = %d\n", count);
	return (count);
}

char	**twisted_fill_splitted(const char *s, const char *charset, 
		char **splitted, size_t *j)
{
	size_t	i1;
	size_t	i2;

	i1 = 0;
	i2 = 0;
	while (s[i1])
	{
		i1 = i2;
		if (is_sep(s[i2], charset))
		{
			while (s[i2] && is_sep(s[i2], charset))
			{
				i2++;
				if (s[i2] && is_sep(s[i2], charset) && s[i2 - 1] != s[i2])
					break ;
			}
			if (i2 > i1)
			{
				splitted[*j] = ft_substr(s, i1, i2 - i1);
				if (!splitted[*j])
					return (free_words(splitted));
				(*j)++;
			}
		}
		else
		{
			while (s[i2] && !is_sep(s[i2], charset))
				i2++;
			if (i2 > i1)
			{
				splitted[*j] = ft_substr(s, i1, i2 - i1);
				if (!splitted[*j])
					return (free_words(splitted));
				(*j)++;
			}
		}
	}
	return (splitted);
}

char	**fill_meta_words(char **splitted, char **command, const char *charset)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	//(void)charset;
	while (command[k])
	{
		if (command[k][0] == D_QUOTE || command[k][0] == S_QUOTE)
		{
			splitted[i] = ft_substr(command[k], 0, ft_strlen(command[k]));
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
	char	**splitted;
	int		count;
	const	char	charset[4] = {'>', '<', '|', 0};

	count = split_meta_count(command, charset);
	splitted = malloc((count + 1) * sizeof(char *));
	if (!splitted)
		return (free_words(command));
	splitted = fill_meta_words(splitted, command, charset);
	free_words(command);
	if (!splitted)
		return (NULL);
	return (splitted);
}