/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:48:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/02 16:29:11 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup2_pb(t_content *content, char *str)
{
	ft_putstr_fd("maxishell: ", STDERR_FILENO);
	perror(str);
	content->array_ptr->content->error_code = 1;
	if(content->outfile != -2)
	{
		close(content->outfile);
		content->outfile = -2;
	}
	if(content->infile != -2)
	{
		close(content->infile);
		content->infile = -2;
	}
	return(O_ERROR);
}

void	ft_exec_failure(t_expar *expar, int i)
{
	if (i == 1)
		perror("pipe");
	if (i == 2)
		perror("fork");
	free(expar->options);
	return;
}