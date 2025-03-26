/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:11:49 by nofanizz          #+#    #+#             */
/*   Updated: 2024/11/12 11:10:12 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	r;
	size_t	lengthsrc;
	size_t	lengthdest;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	lengthdest = ft_strlen(dest);
	lengthsrc = ft_strlen(src);
	r = lengthdest;
	if (size <= r)
		return (lengthsrc + size);
	while (i < size - lengthdest - 1 && src[i] != '\0')
	{
		dest[r] = src[i];
		r++;
		i++;
	}
	dest[r] = '\0';
	return (lengthsrc + lengthdest);
}
