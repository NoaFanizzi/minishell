/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_cmd_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:24:36 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/07 18:17:01 by nbodin           ###   ########lyon.fr   */
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
		else if (ft_strncmp(cmd[i], "<", 1) != 0
			|| ft_strncmp(cmd[i], ">", 1) != 0)
			break ;
		i++;
	}
	return (count);
}

int	copy_opt(t_content *content, char **cmd, size_t *j, size_t i)
{
	content->cmd[(*j)++] = ft_strdup(cmd[i]);
	if (!content->cmd[*j - 1])
	{
		free(content->cmd[0]);
		return (1);
	}
	return (0);
}

int	assign_cmd_and_opt(char **cmd, t_content *content)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	content->cmd[j] = ft_strdup(find_command_name(cmd, &i)); //TODO Protect this strdup which is causing some leaks
	if (!content->cmd[j])
		return (1);
	rem_and_shift(content->cmd[j]);
	switch_back_lit_quotes(content->cmd[j]);
	j++;
	while (cmd[++i])
	{
		if (cmd[i][0] == '-')
		{
			if (copy_opt(content, cmd, &j, i))
				return (1);
		}
		else if (ft_strncmp(cmd[i], "<", 1) != 0
			&& ft_strncmp(cmd[i], ">", 1) != 0)
			break ;
		else
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
	content->cmd = ft_calloc(size + 1, sizeof(char *)); //PROTECTED
	if (!content->cmd)
		return (1);
	if (assign_cmd_and_opt(cmd, content))
	{
		free(content->cmd);
		size_t i;

		i = 0;
		while(&content->files[i])
		{
			ft_wipe(&content->files[0].eof);
			i++;
		}
		free(content->files);
		content->files = NULL;
		return (1);
	}
	return (0);
}
