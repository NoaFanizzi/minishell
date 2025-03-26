/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:10:18 by nofanizz          #+#    #+#             */
/*   Updated: 2024/11/11 09:58:39 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	size_t	i;

	i = ft_strlen(string) + 1;
	while (i--)
		if (string[i] == (unsigned char)searchedChar)
			return ((char *)&string[i]);
	return (0);
}
