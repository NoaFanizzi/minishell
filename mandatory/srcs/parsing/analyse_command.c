/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 02:18:03 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_array_size(char ***cmd_splitted, t_array *array)
{
	size_t	i;

	i = 0;
	while (cmd_splitted[i])
	{
		if (cmd_splitted[i][0] && ft_strncmp(cmd_splitted[i][0], "|", 1) != 0)
			array->size++;
		i++;
	}
}

void	fill_struct_size(t_array *array, size_t struct_index)
{
	size_t	i;

	i = 0;
	while (i < struct_index)
		array->content[i++].size = struct_index;
}

void	analyse_command(char ***cmd_splitted, t_array *array)
{
	size_t	cmd_index;
	size_t	struct_index;

	cmd_index = 0;
	struct_index = 0;
	get_array_size(cmd_splitted, array);
	array->content = malloc((array->size) * sizeof(t_content));
	// check malloc
	while (cmd_splitted[cmd_index])
	{
		if (cmd_splitted[cmd_index][0] && strncmp(cmd_splitted[cmd_index][0],
				"|", 1) != 0)
		{
			if (create_hdoc_struct(cmd_splitted[cmd_index],
					&array->content[struct_index]) == -1)
				return ;
			create_cmd_struct(cmd_splitted, &array->content[struct_index],
				cmd_index);
			struct_index++;
		}
		cmd_index++;
	}
	fill_struct_size(array, struct_index);
	return ;
}

// MALLOC AND FT