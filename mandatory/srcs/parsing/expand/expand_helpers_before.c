/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers_before.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:40:18 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/18 09:55:25 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_var_first_char(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

void	*look_to_expand(t_expand *data, t_list **env, t_array *array)
{
	int	returned_value;

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
			returned_value = handle_normal_expand(data, env, array);
			if (returned_value == 1)
				array->p_exit_status = 1;
			if (returned_value == 2)
				array->p_exit_status = 2;
			if (returned_value == 1 || returned_value == 2)
				return (NULL);
		}
	}
	else
		data->i++;
	return ((void *)1);
}
