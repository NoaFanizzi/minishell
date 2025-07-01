/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents_get_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:57:15 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/01 16:57:39 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_redir_dad(t_array *array, t_list **env)
{
	int	stdin_saved;
	int	stdout_saved;
	int command;
	
	stdin_saved = dup(STDIN_FILENO);
	stdout_saved = dup(STDOUT_FILENO);
	command = ft_is_built_in(&array->content[0]);
	
	if(command == 0)
	{
		ft_parse_redirections(&array->content[0]);
		ft_is_built_in_dad(array, env);
		array->p_exit_status = array->content[0].error_code;
	}
	if(command == 1)
	{
		dup2(stdin_saved, STDIN_FILENO);
		close(stdin_saved);
		dup2(stdout_saved, STDOUT_FILENO);
		close(stdout_saved);
		return(1);
	}
	dup2(stdin_saved, STDIN_FILENO);
	close(stdin_saved);
	dup2(stdout_saved, STDOUT_FILENO);
	close(stdout_saved);
	return(0);
}