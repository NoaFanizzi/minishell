/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:03:08 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/01 17:03:27 by nofanizz         ###   ########.fr       */
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

int ft_is_command(t_content *content)
{
	size_t	i;
	char	*adding_slash;

	i = 0;
	if (content->cmd == NULL || !content->cmd[0])
		return (2);
	while (content->expar->options[i])
	{
		adding_slash = ft_strjoin(content->expar->options[i], "/");
		if (!adding_slash)
			return (1);
		content->expar->path = ft_strjoin(adding_slash, content->cmd[0]);
		free(adding_slash);
		if (!content->expar->path)
			return (1);
		if (access(content->expar->path, X_OK) == 0)
			return (0);
		free(content->expar->path);
		content->expar->path = NULL;
		i++;
	}
	if(ft_check_if_command(content->cmd[0], &content->expar->path) == 0)
		return (0);
	return (1);
}