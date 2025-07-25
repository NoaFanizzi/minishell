/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:03:08 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/25 11:54:29 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_command(char *cmd, char **path, t_content *content)
{
	if (access(cmd, X_OK) == 0)
	{
		*path = ft_strdup(cmd);
		if (!(*path))
		{
			ft_open_error(content, NULL);
			ft_exit(content);
		}
		return (0);
	}
	return (1);
}

int	ft_is_dir(char *str, int *exit_code)
{
	struct stat	infos;

	if (stat(str, &infos) == -1)
		return (0);
	if (S_ISDIR(infos.st_mode))
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		*exit_code = 126;
		return (1);
	}
	*exit_code = 0;
	return (0);
}

int	ft_is_path_command(t_content *content)
{
	int	is_command;

	is_command = ft_contains_dir(content);
	if (is_command == 1 && access(content->cmd[0], X_OK) == 0)
	{
		content->expar->path = ft_strdup(content->cmd[0]); // PROTECTED
		if (!content->expar->path)
		{
			ft_open_error(content, content->expar->path);
			content->error_code = 1;
			ft_exit(content);
		}
		return (0);
	}
	if (is_command == 1)
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		ft_exit(content);
	}
	return (1);
}

int	check_command_validity(t_content *content, size_t i, char **adding_slash)
{
	*adding_slash = ft_strjoin(content->expar->options[i], "/"); // PROTECTED
	if (!adding_slash)
	{
		ft_open_error(content, NULL);
		ft_exit(content);
	}
	content->expar->path = ft_strjoin(*adding_slash, content->cmd[0]); // PROTECTED
	free(*adding_slash);
	if (!content->expar->path)
	{
		ft_open_error(content, NULL);
		ft_exit(content);
	}
	if (access(content->expar->path, F_OK) == 0)
	{
		if (access(content->expar->path, X_OK) == 1)
		{
			perror("maxishell: ");
			ft_exit(content);
		}
		if (ft_is_dir(content->cmd[0], &content->error_code) == 1)
			ft_exit(content);
		return (0);
	}
	return (1);
}

int	ft_is_command(t_content *content)
{
	char	*adding_slash;
	size_t	i;

	i = 0;
	if ((content->cmd == NULL || !content->cmd[0])
		|| (ft_strcmp(content->cmd[0], "") == 0))
		return (2);
	if (ft_is_path_command(content) == 0)
		return (0);
	while (content->expar->options[i])
	{
		if (check_command_validity(content, i, &adding_slash) == 0)
			return (0);
		if (ft_is_dir(content->cmd[0], &content->error_code) == 1)
			ft_exit(content);
		free(content->expar->path);
		content->expar->path = NULL;
		i++;
	}
	if (ft_check_if_command(content->cmd[0], &content->expar->path,
			content) == 0)
		return (0);
	return (1);
}
