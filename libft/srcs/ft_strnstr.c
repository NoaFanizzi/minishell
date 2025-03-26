/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:16:57 by nofanizz          #+#    #+#             */
/*   Updated: 2024/11/12 11:10:57 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	p;

	i = 0;
	j = 0;
	p = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	if (len == 0)
		return (NULL);
	while (str[i] && (i < len))
	{
		p = i;
		j = 0;
		while (str[i] == to_find[j] && (i < len))
		{
			if (to_find[j + 1] == '\0')
				return ((char *)&str[i - j]);
			i++;
			j++;
		}
		i = p + 1;
	}
	return (NULL);
}
