/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:12:36 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/26 12:46:26 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_arg(char *cmd)
{
	size_t	i;

	i = 0;
	if (cmd[i] != '-')
		return (1);
	i++;
	if(cmd[i] == '\0')
	{
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(" ", 1);
		return(1);
	}
	while(cmd[i])
	{
		if (cmd[i] != 'n')
		{
			ft_putstr_fd(cmd, 1);
			ft_putstr_fd(" ", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_echo(char **cmd)
{
	int params;

	params = 0;
	if(ft_is_arg(cmd[1]) == 0)
		params = 1;
	ft_putstr_fd(cmd[2], 1);
	if(params == 0)
		ft_putstr_fd("\n", 1);
	return(0);
}
//petit doute sur le putstr