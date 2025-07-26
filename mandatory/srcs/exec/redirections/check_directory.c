/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:19:04 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/26 16:56:28 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_point(t_content *content, char *path)
{
	if (access(path, F_OK) == -1 || !ft_contains_dir(path)
		|| !ft_strcmp(path, "..") || !ft_strcmp(path, ".")) 
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		content->error_code = 127;
		ft_exit(content);
	}
}

