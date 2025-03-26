/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:23:54 by nofanizz          #+#    #+#             */
/*   Updated: 2024/11/06 14:52:17 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*srcc;
	unsigned char		*destt;

	srcc = (const unsigned char *)src;
	destt = (unsigned char *)dest;
	i = 0;
	while (i < n && (dest || src))
	{
		destt[i] = srcc[i];
		i++;
	}
	return (dest);
}
