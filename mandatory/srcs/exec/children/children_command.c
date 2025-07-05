/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:03:08 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/06 00:31:28 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_command(char *cmd, char **path)
{
	if (access(cmd, X_OK) == 0)
	{
		*path = ft_strdup(cmd);
		return (0);
	}
	return (1);
}

int	ft_is_dir(char *str, int *exit_code)
{
	struct stat infos;

	if (stat(str, &infos) == -1)
	{
        return 0;
    }
	if(S_ISDIR(infos.st_mode))
	{
		ft_putstr_fd("maxishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		*exit_code = 126;
		return(1);
	}
	*exit_code = 0;
    return(0);
}


// void	ft_split_command_from_path(t_content *content)
// {
// 	size_t	i;
// 	char *temp;

// 	i = 0;
// 	while(content->cmd[i])
// 	{
// 		ft_substr()
// 	}
// }

int ft_is_path_command(t_content *content)
{
	int	is_command;

	is_command = 0;
    if ((content->cmd[0][0] == '/')
        || (ft_strncmp(content->cmd[0], "./", 2) == 0)
        || (ft_strncmp(content->cmd[0], "../", 3) == 0)
        || (ft_strcmp(content->cmd[0], "..") == 0)
        || (ft_strcmp(content->cmd[0], ".") == 0))
		is_command = 1;
	//printf("salut\n");
	if (is_command == 1 && access(content->cmd[0], X_OK) == 1)
	{
		content->expar->path = ft_strdup(content->cmd[0]);
		return(0);
	}
	printf("AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
	return(1);
}

int ft_is_command(t_content *content)
{
	size_t	i;
	char	*adding_slash;

	i = 0;
	if ((content->cmd == NULL || !content->cmd[0])
		||(ft_strcmp(content->cmd[0], "") == 0))
		return (2);
	// if(ft_is_path_command(content) == 0)
	// 	return(0);
	while (content->expar->options[i])
	{
		adding_slash = ft_strjoin(content->expar->options[i], "/");
		if (!adding_slash)
			return (1);
		content->expar->path = ft_strjoin(adding_slash, content->cmd[0]);
		free(adding_slash);
		if (!content->expar->path)
			return (1);
		//printf("content->expar->path = %s\n", content->expar->path);
		if (access(content->expar->path, F_OK) == 0)
		{
			if (access(content->expar->path, X_OK) == 1)
			{
				perror("maxishell: ");
				ft_exit(content);
			}
			if(ft_is_dir(content->cmd[0], &content->error_code) == 1)
				ft_exit(content);
			return (0);
		}
		if(ft_is_dir(content->cmd[0], &content->error_code) == 1)
			ft_exit(content);
		free(content->expar->path);
		content->expar->path = NULL;
		i++;
	}
	if(ft_check_if_command(content->cmd[0], &content->expar->path) == 0)
		return (0);
	return (1);
}
