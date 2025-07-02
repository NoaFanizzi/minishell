/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_error_code.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:33:15 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/02 17:21:48 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_after_error(t_expar *expar, t_content *content, t_list **env, t_array *array)
{
	ft_free_env(*env);
	ft_free_tab(expar->options);
	free_command(content->cmd_splitted);
	ft_free_array_content(array);
	ft_close_pipes(array);
	//printf("errno = %d\n", errno);
	exit(errno);
}