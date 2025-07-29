/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:40:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 23:07:43 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switch_lit_quotes(char *exp_var)
{
	size_t	i;

	i = 0;
	while (exp_var[i])
	{
		if (exp_var[i] == D_QUOTE || exp_var[i] == S_QUOTE)
			exp_var[i] = exp_var[i] * -1;
		i++;
	}
}

void	switch_back_lit_quotes(char *exp_var)
{
	size_t	i;

	i = 0;
	while (exp_var[i])
	{
		if (exp_var[i] == (D_QUOTE * -1) || exp_var[i] == (S_QUOTE * -1))
			exp_var[i] = exp_var[i] * -1;
		i++;
	}
}

int	expand_var_in_command(t_expand *data, t_list **env, size_t *k,
		char *new_word)
{
	char	*exp_var;
	int		after_great;
	int		return_value;

	after_great = 0;
	return_value = 0;
	exp_var = get_var_value(data->var_name, *env); // PROTECTED
	if (!exp_var)
		return (1);
	switch_lit_quotes(exp_var);
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
	return (0);
}

void	*loop_data_in_expand(t_expand *data, t_list **env, t_array *array,
		char **new_word)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (data->new_command[j])
	{
		if (j == data->i)
		{
			if (expand_var_in_command(data, env, &k, *new_word) == 1)
			{
				free(data->new_command);
				free(new_word);
				array->p_exit_status = 1;
				return (NULL);
			}
			j += get_var_length(&data->new_command[j + 1]);
		}
		else
			(*new_word)[k++] = data->new_command[j++];
	}
	(*new_word)[k] = 0;
	return ((void *)1);
}

char	*expand_var(t_expand *data, t_list **env, t_array *array)
{
	char	*new_word;
	size_t	k;

	k = 0;
	new_word = ft_calloc(data->new_length + 1, sizeof(char)); // PROTECTED
	if (!new_word)
	{
		free(data->var_name);
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		free(data->new_command);
		return (NULL);
	}
	if (loop_data_in_expand(data, env, array, &new_word) == NULL)
		return (NULL);
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
				+ 1) * sizeof(char)); // PROTECTED
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

char	*expand_word(char *command, t_list **env, t_array *array)
{
	t_expand	data;

	data.i = 0;
	data.new_length = 0;
	data.new_command = ft_strdup(command); // PROTECTED
	if (!data.new_command)
	{
		free(command);
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		array->p_exit_status = 1;
		return (NULL);
	}
	free(command);
	while (data.new_command[data.i])
	{
		if (look_to_expand(&data, env, array) == NULL)
		{
			free(data.new_command);
			return (NULL);
		}
	}
	return (data.new_command);
}
