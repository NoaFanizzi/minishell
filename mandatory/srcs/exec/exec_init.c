/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:34:46 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/28 13:02:38 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_exec(t_expar *expar, char **env, t_content *content)
{
	expar->options = ct_get_paths(env);
	if (!expar->options)
		return ;
	if (pipe(expar->pipe) == -1)
		ft_exec_failure(expar, 1);
	expar->pid_1 = fork();
	if (expar->pid_1 == -1)
		ft_exec_failure(expar, 2);
	if (expar->pid_1 == 0)
		ft_first_cmd(expar, content, env);
	expar->pid_2 = fork();
	if (expar->pid_2 == -1)
		ft_exec_failure(expar, 1);
	if (expar->pid_2 == 0)
		ft_second_cmd(expar, content, env);
	else
	{
		close(expar->pipe[0]);
		close(expar->pipe[1]);
	}
	free_tab(expar->options);
}