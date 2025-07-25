/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:12:36 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/25 14:42:19 by nofanizz         ###   ########.fr       */
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
	if (cmd[i] == '\0')
		return (1);
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	launch_echo(t_content *content, size_t i, int is_space)
{
	while (content->cmd[i])
	{
		ft_putstr_fd(content->cmd[i], 1);
		if (content->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		is_space = 1;
		i++;
	}
	if (is_space == 1)
		ft_putstr_fd(" ", 1);
	i = 0;
	if (content->arg)
	{
		while (content->arg[i])
		{
			ft_putstr_fd(content->arg[i], 1);
			if (content->arg[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
}

int	ft_echo(t_content *content)
{
	int		params;
	int		is_space;
	size_t	i;

	params = 0;
	is_space = 0;
	if (content->cmd[1] != NULL && ft_is_arg(content->cmd[1]) == 0)
		params = 1;
	i = 1;
	while (content->cmd[i] && ft_is_arg(content->cmd[i]) == 0)
		i++;
	ft_launch_echo(content, i, is_space);
	if (params == 0)
		ft_putstr_fd("\n", 1);
	content->error_code = 0;
	return (0);
}
