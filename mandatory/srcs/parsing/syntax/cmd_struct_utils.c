/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:27:47 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/20 15:15:13 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_command_name(char **cmd, size_t *i)
{
	while (cmd[*i])
	{
		if ((ft_strncmp(cmd[*i], "<", 1) == 0
				|| ft_strncmp(cmd[*i], ">", 1) == 0))
		{
			if (!cmd[*i + 1] || !cmd[*i + 2])
				return (NULL);
			*i += 2;
		}
		else if (is_var_assign(cmd[*i]))
			(*i)++;
		else
			return (cmd[*i]);
	}
	return (NULL);
}

int	is_var_assign(char *str)
{
	size_t	i;

	i = 0;
	if (!str || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] != '=')
		return (0);
	if (str[i + 1] == '\0')
		return (0);
	return (1);
}

void	skip_opt_and_redirs(char **cmd, size_t *start)
{
	while (cmd[*start])
	{
		if (cmd[*start][0] == '-')
			(*start)++;
		else if (ft_strncmp(cmd[*start], "<", 1) == 0 || ft_strncmp(cmd[*start],
				">", 1) == 0)
			(*start) += 2;
		else
			break ;
	}
}

size_t	count_redir(char **cmd)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "<", 1) == 0 || ft_strncmp(cmd[i], ">", 1) == 0)
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}
