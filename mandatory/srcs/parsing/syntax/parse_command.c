/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:33:52 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/07 18:22:32 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***parse_splitting_part(char ***command, t_array *array)
{
	char	***cmd_splitted;

	cmd_splitted = NULL;
	*command = space_splitting(*command);
	if (!*command)
	{
		array->p_exit_status = 1;
		return (NULL);
	}
	*command = meta_splitting(*command);
	if (!*command)
	{
		array->p_exit_status = 1;
		return (NULL);
	}
	cmd_splitted = command_splitting(*command);
	if (!cmd_splitted)
	{
		free_command(cmd_splitted);
		array->p_exit_status = 1;
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (NULL);
	}
	free_words(*command);
	return (cmd_splitted);
}

char	*prepare_line(char **line, t_list **var, t_array *array)
{
	char	*str;

	str = ft_strdup(*line); //PROTECTED
	if (!str)
	{
		array->p_exit_status = 1;
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (NULL);
	}
	ft_wipe(line);
	str = expand_word(str, var, array);
	if (!str)
	{
		ft_wipe(&str);
		return (NULL);
	}
	return (str);
}

char	***parse_command(char **line, t_list **var, t_array *array)
{
	char	**command;
	char	*str;

	command = NULL;
	str = prepare_line(line, var, array);
	if (!str)
		return (NULL);
	command = quotes_splitting(command, str);
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
