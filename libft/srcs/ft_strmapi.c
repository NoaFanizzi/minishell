/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:18:12 by nofanizz          #+#    #+#             */
/*   Updated: 2024/11/12 13:05:50 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*converted;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	converted = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!converted)
		return (NULL);
	while (s[i])
	{
		converted[i] = (f)(i, s[i]);
		i++;
	}
	converted[i] = '\0';
	return (converted);
}
