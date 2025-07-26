/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:03:08 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/26 17:01:18 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exist(t_content *content, char *path)
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

int	ft_is_path_command(t_content *content)
{
	struct stat	st;

	check_exist(content, content->expar->path);
	if (access(content->expar->path, X_OK) == -1)
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		content->error_code = 126;
		ft_exit(content);
	}
	if (stat(content->expar->path, &st) == 0 && (S_ISDIR(st.st_mode)))
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		content->error_code = 126;
		ft_exit(content);
	}
	return (1);
}

int	check_command_validity(t_content *content, size_t i)
{
	char *adding_slash;

	adding_slash = ft_strjoin(content->expar->options[i], "/"); // PROTECTED
	if (!adding_slash)
	{
		ft_open_error(content, NULL);
		ft_exit(content);
	}
	content->expar->path = ft_strjoin(adding_slash, content->cmd[0]); // PROTECTED
	free(adding_slash);
	if (!content->expar->path)
	{
		ft_open_error(content, NULL);
		ft_exit(content);
	}
	if (access(content->expar->path, F_OK) == 0)
		return (0);
	return (1);
}

int	ft_is_command(t_content *content)
{
	size_t	i;

	i = 0;
	if ((content->cmd == NULL || !content->cmd[0]) 
		|| (ft_strcmp(content->cmd[0], "") == 0) || !content->expar->options)
		return (2);
	content->expar->path = ft_strdup(content->cmd[0]);
	if (!content->expar->path)
	{
		ft_open_error(content, NULL);
		ft_exit(content);
	}
	if (ft_contains_dir(content->expar->path) == 0)
	{
		while (content->expar->options[i])
		{
			free(content->expar->path);
			content->expar->path = NULL;
			if (check_command_validity(content, i) == 0)
				break ;
			i++;
		}
	}
	ft_is_path_command(content);
	return (0);
}
