/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_cmd_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:24:36 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 21:16:20 by nbodin           ###   ########lyon.fr   */
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

int	assign_cmd_and_opt(char **cmd, t_content *content)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	content->cmd[j] = ft_strdup(find_command_name(cmd, &i));
	if (!content->cmd[j])
		return (1);
	rem_and_shift(content->cmd[j]);
	switch_back_lit_quotes(content->cmd[j]);
	j++;
	i++;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			content->cmd[j++] = ft_strdup(cmd[i]);
			if (!content->cmd[j - 1])
			{
				free(content->cmd[0]);
				return (1);
			}
		}
		else if (strncmp(cmd[i], "<", 1) != 0 && strncmp(cmd[i], ">", 1) != 0)
			break ;
		i++;
	}
	content->cmd[j] = NULL;
	return (0);
}

int	identify_cmd_opt(char **cmd, t_content *content)
{
	size_t	size;

	size = count_cmd_opt(cmd);
	content->cmd = NULL;
	if (size == 0)
		return (0);
	content->cmd = ft_calloc(size + 1, sizeof(char *));
	if (!content->cmd)
		return (1);
	if (assign_cmd_and_opt(cmd, content))
	{
		free(content->cmd);
		return (1);
	}
	return (0);
}
