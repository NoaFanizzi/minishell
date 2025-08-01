/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:40:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/01 10:37:26 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	expand_var_in_command(t_expand *data, t_list **env, size_t *k)
{
	char	*exp_var;
	int		after_great;
	int		return_value;

	after_great = 0;
	return_value = 0;
	return_value = get_var_value(data->var_name, *env, &exp_var);
	if (return_value == 1 || return_value == 2)
		return (return_value);
	switch_lit_quotes(exp_var);
	if (is_after_great_var(data->new_word, data->i))
	{
		after_great = 1;
		data->new_word[*k] = D_QUOTE;
		(*k)++;
	}
	ft_strlcat(data->new_word, exp_var, data->new_length);
	*k += ft_strlen(exp_var);
	if (after_great == 1)
	{
		data->new_word[*k] = D_QUOTE;
		(*k)++;
	}
	free(exp_var);
	return (0);
}

int		loop_data_in_expand(t_expand *data, t_list **env, t_array *array)
{
	size_t	j;
	size_t	k;
	int returned_value;

	j = 0;
	k = 0;
	returned_value = 0;
	while (data->new_command[j])
	{
		if (j == data->i)
		{
			returned_value = expand_var_in_command(data, env, &k);
			if (returned_value == 1 || returned_value == 2)
			{
				free(data->new_command);
				free(data->new_word);
				array->p_exit_status = 1;
				if(returned_value == 2)
					array->p_exit_status = 1;
				return (returned_value);
			}
			j += get_var_length(&data->new_command[j + 1]);
		}
		else
			data->new_word[k++] = data->new_command[j++];
	}
	data->new_word[k] = 0;
	return (0);
}

int	expand_var(t_expand *data, t_list **env, t_array *array)
{
	int returned_value;
	
	data->new_word = ft_calloc(data->new_length + 1, sizeof(char));
	if (!data->new_word)
	{
		free(data->var_name);
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		free(data->new_command);
		return (1);
	}
	returned_value = loop_data_in_expand(data, env, array);
	if (returned_value == 1 || returned_value == 2)
		return (returned_value);
	return(0);
}

char	*expand_word(char *command, t_list **env, t_array *array)
{
	t_expand	data;

	data.i = 0;
	data.new_length = 0;
	data.new_command = ft_strdup(command);
	if (!data.new_command)
	{
		free(command);
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		array->p_exit_status = 1;
		return (NULL);
	}
	free(command);
	if(!data.new_command[data.i])
		return(NULL);
	while (data.new_command[data.i])
	{
		if (look_to_expand(&data, env, array) == NULL)
		{
			free(data.new_command);
			data.new_command = NULL;
			return (NULL);
		}
	}
	return (data.new_command);
}
