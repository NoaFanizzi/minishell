/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:57:47 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/26 09:29:52 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_exit(t_content *content)
{
	int	error_code;

	error_code = 0;
	error_code = content->error_code;
	if(content->env)
		ft_free_env(*content->env);
	//ft_display_tab(content->expar->options);
	if(content->expar != NULL)
	{
		ft_free_tab(content->expar->options);
		if(content->expar->path)
			free(content->expar->path);
		free(content->expar);
	}
	if(content->cmd_splitted)
		free_command(content->cmd_splitted);
	if(content->expar)
		ft_close_pipes(content->array_ptr);
	if(content->array_ptr)
		ft_free_array_content(content->array_ptr);
	exit(error_code);
}