/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:52:30 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/30 01:49:18 by nofanizz         ###   ########.fr       */
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

void	*call_expand_var(t_expand *data, t_list **env, t_array *array)
{
	size_t	true_var_length;

	true_var_length = get_true_var_length(data->var_name, *env);
	data->new_length = true_var_length + ft_strlen(data->new_command)
		- get_var_length(&data->new_command[data->i + 1]) + 1;
	if (is_after_great_var(data->new_command, data->i))
		data->new_length += 2;
	data->new_command = expand_var(data, env, array);
	if (!data->new_command)
		return (NULL);
	data->i += true_var_length;
	return ((void *)1);
}

void	*is_not_var(t_expand *data, t_array *array)
{
	if (is_after_great(data->new_command, data->i)
		&& !quotes_after(data->new_command, data->i
			+ get_var_length(&data->new_command[data->i + 1]) - 1))
	{
		printf("maxishell: $%s: ambiguous redirect\n", data->var_name);
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

void	*handle_normal_expand(t_expand *data, t_list **env, t_array *array)
{
	data->var_name = get_var_name(&data->new_command[data->i + 1]);
	if (!data->var_name)
		return (NULL);
	if (var_exists(data->var_name, *env) == 1)
	{
		if (call_expand_var(data, env, array) == NULL)
		{
			free(data->var_name);
			return (NULL);
		}
	}
	else
	{
		if (is_not_var(data, array) == NULL)
			return (NULL);
	}
	free(data->var_name);
	return ((void *)1);
}

void	*look_to_expand(t_expand *data, t_list **env, t_array *array)
{
	if (data->new_command[data->i] == '$'
		&& is_not_after_hdoc(data->new_command, data->i)
		&& !is_in_single_quotes(data->new_command, data->i)
		&& valid_var_first_char(data->new_command[data->i + 1]))
	{
		if (data->new_command[data->i + 1] == '?')
		{
			if (handle_expand_error_code(data, array) == NULL)
			{
				array->p_exit_status = 1;
				return (NULL);
			}
		}
		else
		{
			if (handle_normal_expand(data, env, array) == NULL)
			{
				array->p_exit_status = 1;
				return (NULL);
			}
		}
	}
	else
		data->i++;
	return ((void *)1);
}
