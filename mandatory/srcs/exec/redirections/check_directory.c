/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:19:04 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/26 11:38:58 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_point(t_content *content)
{
	if (ft_strcmp(content->cmd[0], ".") == 0)
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": filename argument required\n", STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		content->error_code = 2;
		ft_exit(content);
	}
	if (ft_strncmp(content->cmd[0], "..", 2) == 0)
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		content->error_code = 127;
		ft_exit(content);
	}
}

int	check_slash(t_content *content)
{
	if (ft_strncmp(content->cmd[0], "./", 2) == 0 || ft_strcmp(content->cmd[0],
			"../") == 0)
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		content->error_code = 126;
		ft_exit(content);
	}
	content->expar->path = ft_strdup(content->cmd[0]);
	if (!content->expar->path)
	{
		ft_open_error(content, content->expar->path);
		content->error_code = 1;
		ft_exit(content);
	}
	return (0);
}

void	check_dir(t_content *content, struct stat st)
{
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		content->error_code = 126;
		ft_exit(content);
	}
	else
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		content->error_code = 126;
		ft_exit(content);
	}
}

void	check_dir_availability(t_content *content)
{
	ft_putstr_fd("maxishell: ", STDERR_FILENO);
	ft_putstr_fd(content->cmd[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror("");
	if (errno == ENOENT)
		content->error_code = 127;
	else
		content->error_code = 126;
	ft_exit(content);
}
