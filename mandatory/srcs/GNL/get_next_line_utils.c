/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:24:28 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/27 09:41:53 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_ft_strchr(char *str, char c)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

void	*gnl_ft_calloc(size_t elementCount, size_t elementSize)
{
	size_t	size;
	void	*result;

	size = elementCount * elementSize;
	if (size > 2147483647 || size <= 0)
		return (malloc(sizeof(0)));
	result = malloc(size);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, size);
	return (result);
}
