/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents_get_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:57:15 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/02 18:33:27 by nofanizz         ###   ########.fr       */
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
		return(2);
	}
	return(1);
}

int	ft_get_redir_dad(t_array *array, t_list **env)
{
	int command;
	//////////////////////////
    int invalid_fd = 42; // Supposons qu'il n'est pas ouvert

    // On ferme au cas où il serait valide
    close(invalid_fd);

    // Dup échouera ici
	//////////////////////////
	array->content[0].stdin_saved = dup(STDIN_FILENO);
	if(array->content[0].stdin_saved == -1)
	{
		perror("maxishell: stdin");
		array->content[0].stdin_saved = -2;
		array->content->array_ptr->p_exit_status = 1;
		return(1);
	}
	array->content[0].stdout_saved = dup(STDOUT_FILENO);
	if(array->content[0].stdout_saved == -1)
	{
		perror("maxishell: stdout");
		array->content[0].stdout_saved = -2;
		ft_exit(&array->content[0]);
		array->content->array_ptr->p_exit_status = 1;
		return(1);
	}

	command = ft_is_built_in(&array->content[0]);
	if(command == 0)
	{
		if(ft_deal_with_redir(&array->content[0]) == 0)
			ft_is_built_in_dad(array, env);
		array->p_exit_status = array->content[0].error_code;
	}
	dup2(array->content[0].stdin_saved, STDIN_FILENO);
	close(array->content[0].stdin_saved);
	array->content[0].stdin_saved = -2;
	dup2(array->content[0].stdout_saved, STDOUT_FILENO);
	close(array->content[0].stdout_saved);
	array->content[0].stdout_saved = -2;
	if(command == 1)
		return(exit_in_parent(array));
	return(0);
}
