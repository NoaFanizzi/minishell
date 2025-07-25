/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:23:30 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/25 14:34:18 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_content *content)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		content->array_ptr->is_lost = 1;
		content->error_code = 1;
		ft_putendl_fd("pwd: error retrieving current ", STDERR_FILENO);
		ft_putendl_fd("directory: getcwd: cannot access parent", STDERR_FILENO);
		ft_putendl_fd("directories: No such file or directory", STDERR_FILENO);
		return (1);
	}
	content->error_code = 0;
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
}
