/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:44:56 by nofanizz          #+#    #+#             */
/*   Updated: 2024/11/11 10:35:23 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	size_t			i;
	unsigned char	*block;

	block = (unsigned char *)memoryBlock;
	i = 0;
	while (i < size)
	{
		if (block[i] == (unsigned char)searchedChar)
			return (&block[i]);
		i++;
	}
	return (NULL);
}
