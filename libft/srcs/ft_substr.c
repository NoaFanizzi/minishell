/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:49:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/24 16:47:45 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		result = ft_calloc(1, sizeof(char));
		if (!result)
			return (result);
		return (result);
	}
	if (ft_strlen(s) - start <= len)
		result = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	if (ft_strlen(s) - start > len)
		result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	if (s[start] == '\0')
		return (NULL);
	while (i < len && s[start])
		result[i++] = s[start++];
	result[i] = '\0';
	return (result);
}
