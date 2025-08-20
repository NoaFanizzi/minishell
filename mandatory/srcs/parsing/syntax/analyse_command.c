/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/20 10:16:33 by nbodin           ###   ########lyon.fr   */
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

int	create_structs_loop(char ***cmd_splitted, t_array *array, size_t *cmd_index,
		size_t *struct_index)
{
	if (cmd_splitted[*cmd_index][0]
		&& ft_strncmp(cmd_splitted[*cmd_index][0], "|", 1) != 0)
	{
		if (create_hdoc_struct(cmd_splitted[*cmd_index],
				&array->content[*struct_index], array))
		{
			free_command(cmd_splitted);
			return (1);
		}
		if (create_cmd_struct(cmd_splitted, &array->content[*struct_index],
				*cmd_index, array))
		{
			free_command(cmd_splitted);
			return (1);
		}
		(*struct_index)++;
	}
	(*cmd_index)++;
	return (0);
}

int	analyse_command(char ***cmd_splitted, t_array *array)
{
	size_t	cmd_index;
	size_t	struct_index;

	cmd_index = 0;
	struct_index = 0;
	get_array_size(cmd_splitted, array);
	array->content = malloc((array->size) * sizeof(t_content)); //PROTECTED
	if (!array->content)
	{
		free_command(cmd_splitted);
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		array->p_exit_status = 1;
		return (1);
	}
	while (cmd_splitted[cmd_index])
	{
		if (create_structs_loop(cmd_splitted, array, &cmd_index, &struct_index))
			return (1);
	}
	fill_struct_size(array, struct_index);
	return (0);
}

int	process_command(char *line, t_list **var, t_array *array,
		char ****cmd_splitted)
{
	char	*temp_line;

	temp_line = ft_strdup(line); //PROTECTED
	if (!temp_line)
	{
		free(line);
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		array->p_exit_status = 1;
		return (1);
	}
	if (call_check_syntax(line, temp_line, array))
		return (1);
	ft_wipe(&line);
	*cmd_splitted = parse_command(&temp_line, var, array);
	ft_wipe(&temp_line);
	if (!*cmd_splitted)
		return (1);
	if (analyse_command(*cmd_splitted, array))
		return (1);
	ft_init_exec(var, array);
	free_command(*cmd_splitted);
	ft_free_array_content(array);
	return (0);
}
