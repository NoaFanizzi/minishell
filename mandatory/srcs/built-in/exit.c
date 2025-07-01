/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:57:47 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/01 17:24:37 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_hdoc(t_heredocs *hdoc)
{
	if (!hdoc)
		return;
	if (hdoc->text)
	{
		for (size_t i = 0; i < hdoc->size; i++)
			free(hdoc->text[i]);
		free(hdoc->text);
		hdoc->text = NULL;
	}
	free(hdoc);
	hdoc = NULL;
}

void	ft_check_if_valid_exit(t_content *content)
{
	if((ft_strcmp(content->cmd[0], "exit") == 0)
		&&(ft_tablen(content->arg) > 1))
	{
		ft_putstr_fd("maxishell: exit: too many arguments\n", STDERR_FILENO);
		content->error_code = 1;
	}
}

void	ft_exit(t_content *content)
{
	int	error_code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!content)
		exit(1);
	ft_check_if_valid_exit(content);
	error_code = content->error_code;
	if (content->env)
		ft_free_env(*(content->env));
	if (content->expar)
		ft_close_all(content);
	if (content->expar)
	{
		ft_free_tab(content->expar->options);
		free(content->expar->path);
		free(content->expar);
	}
	if (content->cmd_splitted)
		free_command(content->cmd_splitted);
	if (content->array_ptr)
		ft_free_array_content(content->array_ptr);

	exit(error_code);
}

