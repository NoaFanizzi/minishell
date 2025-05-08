/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:06:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/05/08 17:20:51 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
 
int		ft_isspace(char c)
{
	if ((9 <= c && c  <= 13) || (c == 32))
		return (1);
	return (0);
}

char	**contigous_quotes(char **command)
{
	size_t	i;

	i = 0;
	while (command[i])
	{
		if (command[i][0] == D_QUOTE || command[i][0] == S_QUOTE)
		{
			if (i > 0 && ft_isspace(command[i - 1][ft_strlen(command[i - 1]) - 1]) == 0)
				//join with the previous
		}
		if (command[i][0] == D_QUOTE || command[i][0] == S_QUOTE)
		{
			if (command[i + 1] && ft_isspace(command[i + 1][0]) == 0)
				//join with the next
		}
		i++;
	}
}