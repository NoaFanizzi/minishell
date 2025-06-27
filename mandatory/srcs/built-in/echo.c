/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:12:36 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/27 11:53:16 by nofanizz         ###   ########.fr       */
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

int	ft_echo(t_content *content)
{
	int params;
	char *status;
	size_t	i;

	params = 0;
	i = 0;
	if(content->cmd[1] != NULL && ft_is_arg(content->cmd[1]) == 0)
		params = 1;
	if(content->arg)
	{
		while(content->arg[i])
		{
			if(ft_strncmp(content->arg[i], "$?", 2) == 0 && ft_strlen(content->arg[i]) == 2)
			{
				status = ft_itoa(content->array_ptr->p_exit_status);
				ft_putstr_fd(status, 1);
				free(status);
			}
			else
				ft_putstr_fd(content->arg[i], 1);
			if (content->arg[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if(params == 0)
		ft_putstr_fd("\n", 1);
	return(0);
}
//petit doute sur le putstr