/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:17:56 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/28 22:25:00 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_long_min_max(char *str, size_t *i)
{
	if (str[0] == '-')
	{
		if (ft_strcmp("-9223372036854775808", &str[0]) > 0
			&& ft_strlen(&str[*i]) >= 21)
			return (1);
		*i += 1;
	}
	else
	{
		if (str[0] == '+')
			*i += 1;
		if (ft_strcmp("9223372036854775807", &str[*i]) > 0
			&& ft_strlen(&str[*i]) >= 20)
			return (1);
	}
	return (0);
}

void	ft_display_int_array(int *array)
{
	size_t	i;

	i = 0;
	while (i < FD_SETSIZE)
	{
		printf("array[i] = %d\n", array[i]);
		i++;
	}
}

void	ft_fill_array(int *tab)
{
	size_t	i;

	i = 0;
	while (i < FD_SETSIZE)
	{
		tab[i] = -8;
		i++;
	}
}
