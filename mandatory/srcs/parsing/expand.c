/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:40:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/05/22 16:07:33 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	expand(char **command)
{
	size_t	i;

	i = 0;
	while (command[i])
	{
		if (command[i][0] == S_QUOTE)
			i++;
		else
		{
			command[i] = expand_word(command[i]);
			if (!command[i])
				return ;
		}
	}
}

int	valid_var_first_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

int	valid_var_char(char c)
{
	if (ft_isalphanum(c) || c == '_')
		return (1);
	return (0);
}

size_t	get_var_length(char *word)
{
	size_t	len;
	
	len = 0;
	while (word[len] && valid_var_char(word[len]))
		len++;
	return (len + 1);
}

char	*get_var_name(char *word)
{
	size_t	i;
	char	*var_name;

	i = 0;
	while (word[i] && valid_var_char(word[i]))
		i++;
	var_name = ft_substr(word, 0, i);
	if (!var_name)
		return (NULL);
	return (var_name);
}

char	*expand_var_in_word(char *word, size_t	i, size_t size, char *var_name)
{
	char	*new_word;
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	new_word = malloc(size * sizeof(char));
	if (!new_word)
		return (NULL);
	while (word[j])
	{
		if (j == i)
		{
			ft_strlcat(new_word, var_name, size);
			k += get_true_var_length(var_name);
			j += get_var_length(&word[j + 1]);
		}
		else
		{
			new_word[k] = word[j];
			j++;
			k++;
		}
	}
	new_word[k] = 0;
	return (new_word);
}

char	*expand_word(char *word)
{
	char	*var_name;
	char	new_word;
	size_t	i;
	size_t	true_var_length;
	size_t	new_length;

	i = 0;
	true_var_length = 0;
	new_length = 0;
	new_word = NULL;
	while (word[i])
	{
		if (word[i] == '$' && valid_var_first_char(word[i + 1]))
		{
			var_name = get_var_name(&word[i + 1]);
			if (!var_name)
				return (NULL);
			if (var_exists(var_name))
			{
				true_var_length = get_true_var_length(var_name);
				new_length = true_var_length + (ft_strlen(word) - get_var_length(&word[i + 1])) + 1;
				new_word = expand_var_in_word(word, i, new_length, var_name);
				if (!new_word)
					return (NULL);
				i += true_var_length;
			}
		}
		else
			i++;
	}
	if (!new_word)
		return (word);
	free(word);
	return (new_word);
}