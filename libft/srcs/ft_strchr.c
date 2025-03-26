/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:00:30 by nofanizz          #+#    #+#             */
/*   Updated: 2024/11/12 11:24:19 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	size_t	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == (unsigned char)searchedChar)
			return ((char *)&string[i]);
		i++;
	}
	if (string[i] == (unsigned char)searchedChar
		&& (unsigned char)searchedChar == 0)
		return ((char *)&string[i]);
	return (0);
}
