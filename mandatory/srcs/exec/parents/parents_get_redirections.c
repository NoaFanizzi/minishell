/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents_get_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:57:15 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/07 15:04:17 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_in_parent(t_array *array)
{
	if (array->content->cmd && ft_strcmp(array->content[0].cmd[0], "exit") == 0)
	{
		if (array->content[0].arg)
			array->content[0].error_code = ft_atoi(array->content->arg[0]);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_exit(&array->content[0]);
		array->p_exit_status = array->content[0].error_code;
		return (2);
	}
	return (1);
}

int	ft_save_stdin(t_array *array)
{
	array->content[0].stdin_saved = dup(STDIN_FILENO); // PROTECTED
	if (array->content[0].stdin_saved == -1)
	{
		array->content[0].stdin_saved = -2;
		return (ft_dup2_pb(&array->content[0], "stdin"));
	}
	array->content[0].stdout_saved = dup(STDOUT_FILENO); // PROTECTED
	if (array->content[0].stdout_saved == -1)
	{
		array->content->stdout_saved = -2;
		return (ft_dup2_pb(&array->content[0], "stdout"));
	}
	return (0);
}

int	ft_restore_in_out(t_array *array)
{
	if (dup2(array->content[0].stdin_saved, STDIN_FILENO) == -1) // PROTECTED
		return (ft_dup2_pb(&array->content[0], "stdin"));
	close(array->content[0].stdin_saved);
	array->content[0].stdin_saved = -2;
	if (dup2(array->content[0].stdout_saved, STDOUT_FILENO) == -1) // PROTECTED
		return (ft_dup2_pb(&array->content[0], "stdout"));
	close(array->content[0].stdout_saved);
	array->content[0].stdout_saved = -2;
	return (0);
}

int	manage_command_in_parent(t_array *array, int command, t_list **env)
{
	if (command == 0)
	{
		if (ft_deal_with_redir_parents(&array->content[0]) == 0)
		{
			if (ft_is_built_in_dad(array, env) == 1)
			{
				array->p_exit_status = 1;
				return (0);
			}
		}
		else
		{
			array->p_exit_status = 1;
			return (0);
		}
		array->p_exit_status = array->content[0].error_code;
	}
	return (1);
}

int	ft_get_redir_dad(t_array *array, t_list **env)
{
	int	command;
	int	returned_value;

	command = 0;
	if (ft_save_stdin(array) == O_ERROR)
		return (0);
	command = ft_is_built_in(&array->content[0]);
	returned_value = manage_command_in_parent(array, command, env);
	if (ft_restore_in_out(array) == O_ERROR)
		return (O_ERROR);
	if (returned_value == 0)
		return (0);
	if (command == 1)
		return (exit_in_parent(array));
	return (0);
}
