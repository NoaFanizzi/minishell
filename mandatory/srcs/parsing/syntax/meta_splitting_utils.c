/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_splitting_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:34:16 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/19 18:32:56 by nbodin           ###   ########lyon.fr   */
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

int	add_segment(const char *s, char ***splitted, size_t *j, int tab[2])
{
	if (tab[1] > tab[0])
	{
		(void)s;
		(*splitted)[*j] = ft_substr(s, tab[0], tab[1] - tab[0]);//PROTECTED
		if (!(*splitted)[*j])
			return (1);
		(*j)++;
	}
	return (0);
}
