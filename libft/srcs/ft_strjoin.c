/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:20:51 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/11 14:40:43 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	length;
	size_t	i;
	size_t	j;
	char	*merged;

	i = 0;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	merged = ft_calloc((length + 1), sizeof(char));
	if (!merged)
		return (NULL);
	while (s1[++j])
	{
		merged[i] = s1[j];
		i++;
	}
	j = -1;
	while (s2[++j])
	{
		merged[i] = s2[j];
		i++;
	}
	return (merged);
}
