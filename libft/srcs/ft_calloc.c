/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:47:26 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/02 15:40:26 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	size_t	size;
	void	*result;

	size = elementCount * elementSize;
	result = malloc(size);
	if (result == NULL)
		return (NULL);
	ft_bzero(&result, size);
	return (result);
}
