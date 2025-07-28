/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:17:56 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/28 16:27:50 by nofanizz         ###   ########.fr       */
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