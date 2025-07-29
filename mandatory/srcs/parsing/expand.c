/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:40:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 02:30:36 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_var_in_command(t_expand *data, t_list **env, size_t *k,
		char *new_word)
{
	char	*exp_var;
	int		after_great;

	after_great = 0;
	exp_var = get_var_value(data->var_name, *env);
	if (is_after_great_var(data->new_command, data->i))
	{
		after_great = 1;
		new_word[*k] = D_QUOTE;
		(*k)++;
	}
	ft_strlcat(new_word, exp_var, data->new_length);
	*k += ft_strlen(exp_var);
	if (after_great == 1)
	{
		new_word[*k] = D_QUOTE;
		(*k)++;
	}
	free(exp_var);
}

char	*expand_var(t_expand *data, t_list **env)
{
	char	*new_word;
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	new_word = ft_calloc(data->new_length + 1, sizeof(char));
	if (!new_word)
	{
		free(data->new_command);
		return (NULL);
	}
	while (data->new_command[j])
	{
		if (j == data->i)
		{
			expand_var_in_command(data, env, &k, new_word);
			j += get_var_length(&data->new_command[j + 1]);
		}
		else
			new_word[k++] = data->new_command[j++];
	}
	new_word[k] = 0;
	free(data->new_command);
	return (new_word);
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

char	*expand_word(char *command, t_list **env, t_array *array)
{
	t_expand	data;

	data.i = 0;
	data.new_length = 0;
	data.new_command = ft_strdup(command);
	if (!data.new_command)
		return (NULL);
	free(command);
	while (data.new_command[data.i])
	{
		if (look_to_expand(&data, env, array) == NULL)
			return (NULL);
	}
	return (data.new_command);
}
