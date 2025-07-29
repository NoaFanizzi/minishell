/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:33:52 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/30 01:24:41 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*exit_status_splitting_part(t_array *array)
{
	array->p_exit_status = 1;
	return (NULL);
}

char	***parse_splitting_part(char ***command, t_array *array)
{
	char	***cmd_splitted;

	cmd_splitted = NULL;
	*command = space_splitting(*command);
	if (!*command)
		return (exit_status_splitting_part(array));
	*command = meta_splitting(*command);
	if (!*command)
		return (exit_status_splitting_part(array));
	cmd_splitted = command_splitting(*command);
	if (!cmd_splitted)
	{
		free_command(cmd_splitted);
		array->p_exit_status = 1;
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (NULL);
	}
	free_words(*command);
	print_cmd_splitted(cmd_splitted);
	return (cmd_splitted);
}

char	***parse_command(char **line, t_list **var, t_array *array)
{
	char	**command;
	char	*str;

	command = NULL;
	str = ft_strdup(*line); // PROTECTED
	if (!str)
	{
		array->p_exit_status = 1;
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (NULL);
	}
	free(*line);
	*line = NULL;
	str = expand_word(str, var, array);
	if (!str)
	{
		free(str);
		return (NULL);
	}
	command = quotes_splitting(command, str); // PROTECTED
	free(str);
	if (!command)
	{
		array->p_exit_status = 1;
		return (NULL);
	}
	if (contiguous_quotes(&command) == 1 || !command)
	{
		array->p_exit_status = 1;
		return (NULL);
	}
	return (parse_splitting_part(&command, array));
}
