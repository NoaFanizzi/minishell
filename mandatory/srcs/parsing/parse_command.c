/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:33:52 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 15:50:01 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***parse_splitting_part(char ***command)
{
	char	***cmd_splitted;

	cmd_splitted = NULL;
	*command = space_splitting(*command);
	if (!*command)
		return (NULL);
	*command = meta_splitting(*command);
	if (!*command)
		return (NULL);
	cmd_splitted = command_splitting(*command);
	if (!cmd_splitted)
		return (NULL);
	free_words(*command);
	print_cmd_splitted(cmd_splitted);
	return (cmd_splitted);
}

char	***parse_command(char **line, t_list **var, t_array *array)
{
	char	**command;
	char	*str;

	command = NULL;
	str = ft_strdup(*line);
	if (!str)
		return (NULL);
	free(*line);
	*line = NULL;
	str = expand_word(str, var, array);
	if (!str)
		return (NULL);
	command = quotes_splitting(command, str);
	free(str);
	if (!command)
		return (NULL);
	contiguous_quotes(&command);
	if (!command)
		return (NULL);
	return (parse_splitting_part(&command));
}
