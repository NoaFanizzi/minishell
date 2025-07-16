/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:12:36 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/16 14:28:04 by nofanizz         ###   ########.fr       */
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
			// ft_putstr_fd(cmd, 1);
			// ft_putstr_fd(" ", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_echo(t_content *content)
{
	int params;
	int is_space;
	size_t	i;

	params = 0;
	is_space = 0;

	if(ft_strcmp(content->arg[0], "$?") == 0)
	{
		printf("%d\n", content->array_ptr->p_exit_status);
		return(0);
	}
	if(content->cmd[1] != NULL && ft_is_arg(content->cmd[1]) == 0)
		params = 1;
	i = 1;
	while(content->cmd[i] && ft_is_arg(content->cmd[i]) == 0)
		i++;
	while(content->cmd[i])
	{
		ft_putstr_fd(content->cmd[i], 1);
		if(content->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		is_space = 1;
		i++;
	}
	if(is_space == 1)
		ft_putstr_fd(" ", 1);
	i = 0;
	if(content->arg)
	{
		while(content->arg[i])
		{
			ft_putstr_fd(content->arg[i], 1);
			if (content->arg[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if(params == 0)
		ft_putstr_fd("\n", 1);
	content->error_code = 0;
	return(0);
}
//petit doute sur le putstr