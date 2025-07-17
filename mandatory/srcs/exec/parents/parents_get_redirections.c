/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents_get_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:57:15 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/17 17:43:31 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_in_parent(t_array *array)
{
	if(array->content->cmd && ft_strcmp(array->content[0].cmd[0], "exit") == 0)
	{
		if(array->content[0].arg)
			array->content[0].error_code = ft_atoi(array->content->arg[0]);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_exit(&array->content[0]);
		array->p_exit_status = array->content[0].error_code;
		return(2);
	}
	return(1);
}

// ft_dup_in_dad

int	ft_save_stdin(t_array *array)
{
	array->content[0].stdin_saved = dup(STDIN_FILENO);
	if(array->content[0].stdin_saved == -1)
		return(ft_dup2_pb(&array->content[0], "stdin"));
	array->content[0].stdout_saved = dup(STDOUT_FILENO);
	if(array->content[0].stdout_saved == -1)
		return(ft_dup2_pb(&array->content[0], "stdout"));
	return(0);
}

int	ft_get_redir_dad(t_array *array, t_list **env)
{
	int command;
	
	command = 0;
	
	if(ft_save_stdin(array) == O_ERROR)
		return(O_ERROR);
	command = ft_is_built_in(&array->content[0]);
	if(command == 0)
	{
		if(ft_deal_with_redir(&array->content[0]) == 0)
			ft_is_built_in_dad(array, env);
		array->p_exit_status = array->content[0].error_code;
	}
	if (dup2(array->content[0].stdin_saved, STDIN_FILENO) == -1)
		return (ft_dup2_pb(&array->content[0], "stdin"));
	close (array->content[0].stdin_saved);
	array->content[0].stdin_saved = -2;
	if (dup2(array->content[0].stdout_saved, STDOUT_FILENO) == -1)
		return (ft_dup2_pb(&array->content[0], "stdout"));
	close (array->content[0].stdout_saved);
	array->content[0].stdout_saved = -2;
	if (command == 1)
		return(exit_in_parent(array));
	return(0);
}
