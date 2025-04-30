/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:12:36 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/30 13:53:24 by nofanizz         ###   ########.fr       */
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

	params = 0;

	if(content->cmd[1] != NULL && ft_is_arg(content->cmd[1]) == 0)
		params = 1;
	ft_putstr_fd(content->arg, 1);
	if(params == 0)
		ft_putstr_fd("\n", 1);
	//ft_close_all(expar, content);
	//ft_free_tab(expar->options);
	//ft_free_content(content);
	//exit(0);
	return(0);
}
//petit doute sur le putstr