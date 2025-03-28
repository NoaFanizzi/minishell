/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:48:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/28 13:49:39 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_content(t_content *content)
{
	if(content->cmd)
		ft_free_tab(content->cmd);
	if(content->arg)
		free(content->arg);
}

void	ft_dup2_pb(t_expar *expar, t_content *content)
{
	free_tab(expar->options);
	free(expar->path);
	free_content(content);
	ft_close_all(expar);
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
	exit(EXIT_FAILURE);
}