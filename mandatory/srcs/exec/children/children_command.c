/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:03:08 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/06 19:53:18 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_f_ok(t_content *content, char *path)
{
	if (access(path, F_OK) == -1)
	{
		if (!(*content->env) && !ft_contains_dir(path))
		{
			ft_putstr_fd("maxishell: ", STDERR_FILENO);
			ft_putstr_fd(content->cmd[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			content->error_code = 127;
			ft_exit(content);
		}
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
		content->error_code = 126;
		ft_exit(content);
	}
}

void	check_exist(t_content *content, char *path)
{
	struct stat	st;

	if (ft_contains_dir(path))
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
		content->error_code = 127;
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
}

int	ft_is_path_command(t_content *content)
{
	if (!ft_strncmp(content->expar->path, "..", 2)
		|| !ft_strcmp(content->expar->path, ".") || !ft_strchr(content->expar->path, '/'))
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		content->error_code = 127;
		ft_exit(content);
	}
	if (access(content->expar->path, F_OK) == 0)
	{
		if (access(content->expar->path, X_OK) == -1)
		{
			ft_putstr_fd("maxishell: ", STDERR_FILENO);
			ft_putstr_fd(content->cmd[0], STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			content->error_code = 126;
			ft_exit(content);
		}
		return (0);
	}
	check_exist(content, content->expar->path);
	return (1);
}

int	check_command_validity(t_content *content, size_t i)
{
	char	*adding_slash;

	adding_slash = ft_strjoin(content->expar->options[i], "/");
	if (!adding_slash)
	{
		ft_open_error(content, NULL);
		ft_exit(content);
	}
	content->expar->path = ft_strjoin(adding_slash, content->cmd[0]);
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

int	check_validity_in_dir(t_content *content)
{
	size_t	i;

	i = 0;
	if (ft_contains_dir(content->expar->path) == 0)
	{
		while (content->expar->options && content->expar->options[i])
		{
			free(content->expar->path);
			content->expar->path = NULL;
			if (check_command_validity(content, i) == 0)
				return (0);
			i++;
		}
	}
	return (1);
}
