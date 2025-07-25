/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_error_code.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:33:15 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/25 14:39:05 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_right_error_code(t_content *content)
{
	if (content->error_code != -5)
		return (content->error_code);
	else
		return (content->array_ptr->p_exit_status);
}

void	ft_free_after_error(t_expar *expar, t_content *content, t_list **env,
		t_array *array)
{
	ft_free_env(*env);
	ft_free_tab(expar->options);
	free_command(content->cmd_splitted);
	ft_free_array_content(array);
	ft_close_pipes(array);
	// printf("errno = %d\n", errno);
	exit(errno);
}

int	ft_open_error(t_content *content, char *str)
{
	char	*error_message;

	error_message = NULL;
	error_message = ft_strjoin("maxishell: ", str);
	if (!error_message)
	{
		perror("maxishell: malloc");
		error_message = NULL;
		content->error_code = 1;
		return (O_ERROR);
	}
	perror(error_message);
	free(error_message);
	ft_close_all(content);
	content->error_code = 1;
	return (O_ERROR);
}

int	ft_dup2_pb(t_content *content, char *str)
{
	char	*error_message;

	error_message = NULL;
	error_message = ft_strjoin("maxishell: ", str);
	if (!error_message)
	{
		perror("maxishell: malloc");
		error_message = NULL;
		content->error_code = 1;
		return (O_ERROR);
	}
	perror(error_message);
	free(error_message);
	ft_close_all(content);
	content->error_code = 1;
	content->array_ptr->p_exit_status = 1;
	return (O_ERROR);
}
