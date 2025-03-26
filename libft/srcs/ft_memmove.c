/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:24:58 by nofanizz          #+#    #+#             */
/*   Updated: 2024/11/12 11:23:46 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *d, const void *s, size_t size)
{
	unsigned char	*dest;
	unsigned char	*src;
	size_t			i;

	i = 0;
	dest = (unsigned char *)d;
	src = (unsigned char *)s;
	if (d > s)
		while (size-- && (d || s))
			dest[size] = src[size];
	else
	{
		while (i < size && (d || s))
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (d);
}
