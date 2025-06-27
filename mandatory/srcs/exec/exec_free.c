/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:48:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/26 09:10:40 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup2_pb(t_content *content)
{
	ft_free_tab(content->expar->options);
	free(content->expar->path);
	ft_free_content(content);
	//ft_close_all(expar, content);
	perror("Dup2 error");
	exit(1);
}

void	ft_exec_failure(t_expar *expar, int i)
{
	if (i == 1)
		perror("pipe");
	if (i == 2)
		perror("fork");
	free(expar->options);
	g_exit_status = errno;
	return;
}