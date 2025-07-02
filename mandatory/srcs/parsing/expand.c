/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:40:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/02 19:02:15 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	valid_var_first_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

int	valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
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

char	*expand_var_in_command(char *word, size_t	i, size_t size, char *var_name, t_list **env)
{
	char	*new_word;
	char 	*exp_var; //la vraie valeur de la variable expand
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	exp_var = NULL;
	new_word = ft_calloc(size + 1, sizeof(char));
	if (!new_word)
		return (NULL);
	while (word[j])
	{
		if (j == i)
		{
			exp_var = get_var_value(var_name, *env);
			ft_strlcat(new_word, exp_var, size); //TODO return la variable (char *)
			k += ft_strlen(exp_var); //TODO donne les length de la var (size_t);
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

int		is_var_quoted(char *command, size_t i)
{
	size_t	j;

	j = 0;
	while (command[j] && j != i)
	{
		if (command[j] == S_QUOTE)
		{
			while (command[j] && j != i && command[j] != S_QUOTE)
				j++;
			if (j == i && command[j] != S_QUOTE)
				return (1);
		}
		else if (command[j] == D_QUOTE)
		{
			while (command[j] && j != i && command[j] != D_QUOTE)
				j++;
			if (j == i && command[j] != D_QUOTE)
				return (2);
		}
		j++;
	}
	return (0);
}

void	skip_till_quote(int quoted,char *command, size_t *i)
{
	if (quoted == 0)
		return ;
	else if (quoted == 1)
	{
		while (*i > 0 && command[*i] != S_QUOTE)
			(*i)--;
	}	
	else if (quoted == 2)
	{
		while (*i > 0 && command[*i] != D_QUOTE)
			(*i)--;
	}
}

int		is_not_after_hdoc(char *command, size_t i)
{
	int	quoted;

	quoted = is_var_quoted(command, i);
	skip_till_quote(quoted, command, &i);
	if (i > 0)
		i--;
	while (i > 0)
	{
		if (command[i] == S_QUOTE)
		{
			i--;
			while (i > 0 && command[i] != S_QUOTE)
				i--; 
			if (i == 0)//to see
				return (1);
		}
		else if (command[i] == D_QUOTE)
		{
			i--;
			while (i > 0 && command[i] != D_QUOTE)
				i--; 
			if (i == 0)//to see
				return (1);
		}
		else if (ft_isspace(command[i]))
		{
			i--;
			while (i > 0 && ft_isspace(command[i]))
				i--;
			if (command[i] != '<' && i > 0 && command[i - 1] != '<')
				return (1);//not an heredoc
		}
		else if (command[i] != '<' && command[i - 1] != '<')
		{
			i -= 2;
			while (i > 0 && !ft_isspace(command[i])
				&& command[i] != S_QUOTE
				&& command[i] != D_QUOTE
				&& (command[i] != '<'
				&& i > 0 && command[i - 1] != '<'))
				i--;
		}
		else
			return (0);
	}
	return (0);
}

char	*expand_word(char *command, t_list **env)
{
	char	*var_name;
	char	*new_command;
	size_t	i;
	size_t	true_var_length;
	size_t	new_length;
	

	i = 0;
	true_var_length = 0;
	new_length = 0;
	new_command = NULL;
	size_t length = ft_strlen(command);
	while (i < length)//command[i] ?
	{
		if (command[i] == '$' && is_not_after_hdoc(command, i) && valid_var_first_char(command[i + 1]))
		{
			var_name = get_var_name(&command[i + 1]);
			if (!var_name)
				return (NULL);
			if (var_exists(var_name, *env) == 1)
			{
				true_var_length = get_true_var_length(var_name, *env);
				new_length = true_var_length + (ft_strlen(command) - get_var_length(&command[i + 1])) + 1;
				new_command = expand_var_in_command(command, i, new_length, var_name, env);
				if (!new_command)
					return (NULL);
				length = ft_strlen(command);
				i = 0;
				continue ;
			}
		}
		else
			i++;
	}
	if (!new_command)
		return (command);
	free(command);
	return (new_command);
}

// size_t	ft_count_dollars(char *str)
// {
// 	size_t	i;
// 	size_t	count;

// 	i = 0;
// 	count = 0;
// 	while(str[i])
// 	{
// 		if(str[i] == '$')
// 			count++;
// 		i++;
// 	}
// 	return(count);
// }
