/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:41:01 by nofanizz          #+#    #+#             */
/*   Updated: 2024/11/12 11:23:16 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_division(int n)
{
	int	length;

	length = 1;
	while (n >= 10)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

static char	*ft_putnbr(char *str, int nb, int length, int sign)
{
	if (sign < 0)
	{
		str[0] = '-';
		length++;
		sign = -sign;
	}
	if (nb >= 10)
		ft_putnbr(str, nb / 10, length - 1, sign);
	str[length - 1] = (nb % 10) + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		s;
	size_t	length;
	char	*str;

	s = 1;
	length = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		s = -s;
		n = -n;
		length++;
	}
	if (n == 0)
		return (ft_strdup("0"));
	length = ft_check_division(n);
	if (s < 0)
		str = ft_calloc(length + 2, sizeof(char));
	if (s > 0)
		str = ft_calloc(length + 1, sizeof(char));
	if (!str)
		return (NULL);
	return (str = ft_putnbr(str, n, length, s));
}
