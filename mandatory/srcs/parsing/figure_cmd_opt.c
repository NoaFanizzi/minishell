/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_cmd_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:24:36 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 15:19:15 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_cmd_opt(char **cmd)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (find_command_name(cmd, &i))
		count++;
	i++;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
			count++;
		else if (strncmp(cmd[i], "<", 1) != 0 || strncmp(cmd[i], ">", 1) != 0)
			break ;
		i++;
	}
	return (count);
}

void	assign_cmd_and_opt(char **cmd, t_content *content)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	content->cmd[j] = ft_strdup(find_command_name(cmd, &i));
	if (!content->cmd[j])
		return ;
	printf("before : %s\n", content->cmd[j]);
	rem_and_shift(content->cmd[j]);
	j++;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
			content->cmd[j++] = ft_strdup(cmd[i]);
		else if (strncmp(cmd[i], "<", 1) != 0 && strncmp(cmd[i], ">", 1) != 0)
			break ;
		i++;
	}
	content->cmd[j] = NULL;
}

void	identify_cmd_opt(char **cmd, t_content *content)
{
	size_t	size;

	size = count_cmd_opt(cmd);
	if (size == 0)
	{
		content->cmd = NULL;
		return ;
	}
	content->cmd = ft_calloc(size + 1, sizeof(char *));
	if (!content->cmd)
		return ;
	assign_cmd_and_opt(cmd, content);
}
