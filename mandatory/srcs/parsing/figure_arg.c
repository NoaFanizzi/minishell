/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:26:53 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 18:42:31 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_real_args(char **cmd, size_t start)
{
	size_t	count;

	count = 0;
	while (cmd[start])
	{
		if (ft_strncmp(cmd[start], "<", 1) == 0 || ft_strncmp(cmd[start], ">",
				1) == 0)
			start += 2;
		else
		{
			count++;
			start++;
		}
	}
	return (count);
}

size_t	count_arg(char **cmd)
{
	size_t	i;

	i = 0;
	if (!find_command_name(cmd, &i))
		return (0);
	i++;
	i = skip_opt_and_redirs(cmd, i);
	return (count_real_args(cmd, i));
}

void	fill_args(char **cmd, size_t start, char **arg)
{
	size_t	j;

	j = 0;
	while (cmd[start])
	{
		if (ft_strncmp(cmd[start], "<", 1) == 0 || ft_strncmp(cmd[start], ">",
				1) == 0)
			start += 2;
		else
		{
			arg[j] = ft_strdup(cmd[start]);
			if (!arg[j])
				return ;
			rem_and_shift(arg[j]);
			switch_back_lit_quotes(arg[j]);
			j++;
			start++;
		}
	}
	arg[j] = NULL;
}

void	identify_arg(char **cmd, t_content *content)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = count_arg(cmd);
	if (count == 0)
	{
		content->arg = NULL;
		return ;
	}
	content->arg = ft_calloc(count + 1, sizeof(char *));
	if (!content->arg)
		return ;
	if (!find_command_name(cmd, &i))
	{
		free(content->arg);
		content->arg = NULL;
		return ;
	}
	i++;
	i = skip_opt_and_redirs(cmd, i);
	fill_args(cmd, i, content->arg);
}
