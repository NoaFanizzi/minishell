/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:40:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/06/26 18:30:25 by nofanizz         ###   ########.fr       */
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

char	*expand_var_in_word(char *word, size_t	i, size_t size, char *var_name, t_list **env)
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

char	*expand_word(char *word, t_list **env)
{
	char	*var_name;
	char	*new_word;
	size_t	i;
	size_t	true_var_length;
	size_t	new_length;

	i = 0;
	true_var_length = 0;
	new_length = 0;
	new_word = NULL;
	
	size_t length = ft_strlen(word);
	//printf("word = %s\n", )
	while (i < length)
	{
		if (word[i] == '$' && valid_var_first_char(word[i + 1]))
		{
			//printf("AAAAAAAA\n");
			var_name = get_var_name(&word[i + 1]);
			//printf("var_name = %s\n", var_name);
			if (!var_name)
				return (NULL);
			if (var_exists(var_name, *env) == 1)//TODO renvoyer 1 si y'a la variable dasn env et 0 sinon (int)
			{
				//printf("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n");
				true_var_length = get_true_var_length(var_name, *env);
				//printf("true_var_length = %zu\n", true_var_length);
				new_length = true_var_length + (ft_strlen(word) - get_var_length(&word[i + 1])) + 1;
				//printf("new_var_length = %zu\n", new_length);
				new_word = expand_var_in_word(word, i, new_length, var_name, env);
				//printf("word = %s\n", word);
				//printf("new_word = %s\n", new_word);
				if (!new_word)
					return (NULL);
				i += true_var_length;
			}
		}
		else
			i++;
		//break;
	}
	if (!new_word)
		return (word);
	free(word);
	return (new_word);
}

size_t	ft_count_dollars(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if(str[i] == '$')
			count++;
		i++;
	}
	return(count);
}

void	expand(char **command, t_list **var)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;

	while (command[i])
	{
		j = 0;
		count = 0;
		count = ft_count_dollars(command[i]);
		if (command[i][0] == S_QUOTE)
			i++;
		else
		{
			while(j < count)
			{
				printf("enterd\n");
				command[i] = expand_word(command[i], var);
				if (!command[i])
					return ;
				j++;
			}
			i++;
		}
	}
}
