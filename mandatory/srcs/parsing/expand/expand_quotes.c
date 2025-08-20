/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:48:16 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/20 10:16:04 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_error_code(char *new_cmd, size_t *k, char *error_code)
{
	ft_strcpy(&new_cmd[*k], error_code);
	*k += ft_strlen(error_code);
	return (2);
}

char	*expand_error_code(char *command, size_t i, t_array *array)
{
	size_t	j;
	size_t	k;
	char	*new_cmd;
	char	*error_code;

	j = 0;
	k = 0;
	if (expand_allocations(array, &new_cmd, &error_code, &command) == NULL)
		return (NULL);
	while (command[j])
	{
		if (j == i)
			j += copy_error_code(new_cmd, &k, error_code);
		else
			new_cmd[k++] = command[j++];
	}
	new_cmd[k] = 0;
	free(command);
	free(error_code);
	return (new_cmd);
}

void	*handle_expand_error_code(t_expand *data, t_array *array)
{
	data->new_command = expand_error_code(data->new_command, data->i, array);
	if (!data->new_command)
		return (NULL);
	data->i++;
	return ((void *)1);
}

void	switch_lit_quotes(char *exp_var)
{
	size_t	i;

	i = 0;
	if (!exp_var)
		return ;
	while (exp_var[i])
	{
		if (exp_var[i] == D_QUOTE || exp_var[i] == S_QUOTE
			|| exp_var[i] == '|' || exp_var[i] == '>'
			|| exp_var[i] == '<')
			exp_var[i] = exp_var[i] * -1;
		i++;
	}
}

void	switch_back_lit_quotes(char *exp_var)
{
	size_t	i;

	i = 0;
	if (!exp_var)
		return ;
	while (exp_var[i])
	{
		if (exp_var[i] == (D_QUOTE * -1) || exp_var[i] == (S_QUOTE * -1)
			|| exp_var[i] == ('|' * -1) || exp_var[i] == ('>' * -1)
			|| exp_var[i] == ('<' * -1))
			exp_var[i] = exp_var[i] * -1;
		i++;
	}
}
