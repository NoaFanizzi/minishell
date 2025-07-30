/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:52:30 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/30 15:25:30 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*expand_allocations(t_array *array, char **new_cmd, char **error_code,
		char **command)
{
	*error_code = ft_itoa(array->p_exit_status);
	if (!*error_code)
	{
		free(*command);
		*command = NULL;
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (NULL);
	}
	*new_cmd = malloc((ft_strlen(*command) - 1 + ft_strlen(*error_code))
			* sizeof(char));
	if (!*new_cmd)
	{
		free(*error_code);
		free(*command);
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (NULL);
	}
	return ((void *)1);
}

int	call_expand_var(t_expand *data, t_list **env, t_array *array)
{
	size_t	true_var_length;
	int returned_value;

	true_var_length = get_true_var_length(data->var_name, *env);
	data->new_length = true_var_length + ft_strlen(data->new_command)
		- get_var_length(&data->new_command[data->i + 1]) + 1;
	if (is_after_great_var(data->new_command, data->i))
		data->new_length += 2;
	returned_value = expand_var(data, env, array, &data->new_command);
	if (returned_value == 1 || returned_value == 2)
		return (returned_value);
	data->i += true_var_length;
	return (0);
}

char	*remove_var(char *command, size_t i)
{
	size_t	j;
	size_t	k;
	char	*new_command;

	j = 0;
	k = 0;
	new_command = malloc((ft_strlen(command) - get_var_length(&command[i + 1])
				+ 1) * sizeof(char));
	if (!new_command)
	{
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		free(command);
		return (NULL);
	}
	while (command[j] && j != i)
		new_command[j++] = command[k++];
	k++;
	while (command[k] && valid_var_char(command[k]))
		k++;
	while (command[k])
		new_command[j++] = command[k++];
	new_command[j] = 0;
	free(command);
	return (new_command);
}

void	*is_not_var(t_expand *data, t_array *array)
{
	if (is_after_great(data->new_command, data->i)
		&& !quotes_after(data->new_command, data->i
			+ get_var_length(&data->new_command[data->i + 1]) - 1))
	{
		ft_putstr_fd("maxishell: $", 2);
		ft_putstr_fd(data->var_name, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		array->p_exit_status = 1;
		return (NULL);
	}
	else
	{
		data->new_command = remove_var(data->new_command, data->i);
		if (!data->new_command)
		{
			free(data->var_name);
			array->p_exit_status = 1;
			return (NULL);
		}
	}
	return ((void *)1);
}

int	handle_normal_expand(t_expand *data, t_list **env, t_array *array)
{
	int	returned_value;
	
	
	data->var_name = get_var_name(&data->new_command[data->i + 1]);
	if (!data->var_name)
		return (1);
	if (var_exists(data->var_name, *env) == 1)
	{
		printf("pour lui la var existe\n");
		returned_value = call_expand_var(data, env, array);
		if (returned_value == 1 || returned_value == 2)
		{
			printf("returned_value of handle_normal_expand = %d\n", handle)
			free(data->var_name);
			return (returned_value);
		}
	}
	else
	{
		printf("pour lui la var n'existe PAS\n");
		if (is_not_var(data, array) == NULL)
			return (1);
	}
	free(data->var_name);
	return (0);
}
