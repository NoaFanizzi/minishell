/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:40:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/28 18:45:07 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	valid_var_first_char(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
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
	printf("var length = %zu\n", len + 1);
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

void	track_quotes_until_meta(int *in_dquote, int *in_squote, char *cmd, size_t *i)
{
	*in_squote = 0;
	*in_dquote = 0;
	while (cmd[*i] && !ft_isspace(cmd[*i]) && cmd[*i] != '|' && cmd[*i] != '<' && cmd[*i] != '>')
	{
		if (!(*in_dquote) && cmd[*i] == '\'')
			*in_squote = !(*in_squote);
		else if (!(*in_squote) && cmd[*i] == '"')
			*in_dquote = !(*in_dquote);
		(*i)++;
	}
}

void	skip_redir_spaces(char *cmd, size_t *i)
{
	while (cmd[*i] && (cmd[*i] == '>' || cmd[*i] == '<'))
		(*i)++;
	while (cmd[*i] && ft_isspace(cmd[*i]))
		(*i)++;
}

int is_after_great_var(char *cmd, size_t var_index)
{
    size_t	i;
	size_t	token_start;
    int in_squote;
    int in_dquote;

	i = 0;
	in_squote = 0;
    in_dquote = 0;
    while (cmd[i])
    {
        handle_quote_state(&in_squote, &in_dquote, cmd, &i);
        if (!in_squote && !in_dquote && (cmd[i] == '>' || cmd[i] == '<'))
        {
        	skip_redir_spaces(cmd, &i);
            token_start = i;
            track_quotes_until_meta(&in_squote, &in_dquote, cmd, &i);
			if (var_index >= token_start && var_index < i)
				return (1);
        }
        else
            i++;
    }
    return (0);
}

int is_after_great(char *cmd, size_t var_index)
{
    size_t	i;
    int in_squote;
    int in_dquote;

	i = 0;
	in_squote = 0;
    in_dquote = 0;
    while (cmd[i])
    {
    	handle_quote_state(&in_squote, &in_dquote, cmd, &i);
        if (!in_squote && !in_dquote && (cmd[i] == '>' || cmd[i] == '<'))
        {
        	skip_redir_spaces(cmd, &i);
            if (i == var_index)
                return 1;
            track_quotes_until_meta(&in_squote, &in_dquote, cmd, &i);
        }
        else
            i++;
    }
    return 0; // Not after >
}

void expand_var_in_command(t_expand *data, t_list **env, size_t *k, char *new_word)
{
	char *exp_var;
	int	after_great;
	
	after_great = 0;
	exp_var = get_var_value(data->var_name, *env);
	if (is_after_great_var(data->new_command, data->i))
	{
		after_great = 1;
		new_word[*k] = D_QUOTE;
		(*k)++;
	}
	ft_strlcat(new_word, exp_var, data->new_length); //TODO return la variable (char *)
	*k += ft_strlen(exp_var); //TODO donne les length de la var (size_t);
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

int	track_var_in_del(char *cmd, size_t *i, size_t var_index)
{
	int in_squote;
	int in_dquote;
	
	in_squote = 0;
	in_dquote = 0;
	while (cmd[*i])
	{
		if (*i == var_index)
			return (0);
		if (!in_dquote && cmd[*i] == '\'')
			in_squote = !in_squote;
		else if (!in_squote && cmd[*i] == '"')
			in_dquote = !in_dquote;
		if (!in_squote && !in_dquote &&
			(ft_isspace(cmd[*i]) || cmd[*i] == '|' ||
				cmd[*i] == '<' || cmd[*i] == '>' || cmd[*i] == '\0'))
			break;
		(*i)++;
	}
	return (1);
}

int is_not_after_hdoc(char *cmd, size_t var_index)
{
	size_t i = 0;
	int in_squote = 0;
	int in_dquote = 0;

	while (cmd[i])
	{
		handle_quote_state(&in_squote, &in_dquote, cmd, &i);
		if (!in_squote && !in_dquote && cmd[i] == '<' && cmd[i + 1] == '<')
		{
			i += 2;
			while (cmd[i] && ft_isspace(cmd[i]))
				i++;
			if (track_var_in_del(cmd, &i, var_index) == 0)
				return (0);
		}
		else
			i++;
	}
	return (1);
}


char *remove_var(char *command, size_t i)
{
	size_t j;
	size_t	k;
	char	*new_command;

	j = 0;
	k = 0;
	new_command = malloc((ft_strlen(command) - get_var_length(&command[i + 1])  + 1) * sizeof(char));
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

int is_in_single_quotes(const char *cmd, size_t pos)
{
	int in_squote;
	int in_dquote;
	size_t i;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (i < pos && cmd[i])
	{
		if (!in_dquote && cmd[i] == '\'')
			in_squote = !in_squote;
		else if (!in_squote && cmd[i] == '"')
			in_dquote = !in_dquote;
		i++;
	}
	return in_squote;
}

char	copy_error_code(char *new_cmd, size_t *k, char *command, char *error_code)
{
	new_cmd[*k] = 0;
	ft_strlcat(new_cmd, error_code, ft_strlen(command) - 2 + ft_strlen(error_code));
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
	error_code = ft_itoa(array->p_exit_status);
	new_cmd = malloc((ft_strlen(command) - 1 + ft_strlen(error_code)) * sizeof(char));
	if (!new_cmd)
	{
		free(command);
		return (NULL);
	}
	while (command[j])
	{
		if (j == i)
			j += copy_error_code(new_cmd, &k, command, error_code);
		else
			new_cmd[k++] = command[j++];
	}
	new_cmd[k] = 0;
	free(command);
	return (new_cmd);
} 

int quotes_after(char *cmd, size_t i)
{
    int in_squote;
    int in_dquote;
    size_t j;

	j = 0;
	in_squote = 0;
	in_dquote = 0;
    while (cmd[j] && j <= i)
    {
        if (!in_dquote && cmd[j] == '\'')
            in_squote = !in_squote;
        else if (!in_squote && cmd[j] == '"')
            in_dquote = !in_dquote;
        j++;
    }
    if (in_squote || in_dquote)
        return (0);
    if (!cmd[j])
        return (0);
    if (cmd[j] == '\'' || cmd[j] == '"')
        return (1);
    return (0);
}

void	*handle_expand_error_code(t_expand *data, t_array *array)
{
	data->new_command = expand_error_code(data->new_command, data->i , array);
	if (!data->new_command)
	{
		printf("HERE6\n");
		return (NULL);
	}
	data->i++;
	return (void*)1;
}

void	*call_expand_var(t_expand *data, t_list **env)
{
	size_t	true_var_length;
	
	true_var_length = get_true_var_length(data->var_name, *env);
	data->new_length = true_var_length + ft_strlen(data->new_command) - get_var_length(&data->new_command[data->i + 1]) + 1;
	if (is_after_great_var(data->new_command, data->i))
		data->new_length += 2;
	data->new_command = expand_var(data, env);
	if (!data->new_command)
		return (NULL);
	data->i += true_var_length;
	return ((void *)1);
}

void	*handle_normal_expand(t_expand *data, t_list **env)
{
	data->var_name = get_var_name(&data->new_command[data->i + 1]);
	if (!data->var_name)
		return (NULL);
	if (var_exists(data->var_name, *env))
	{
		if (call_expand_var(data, env) == NULL)
		{
			printf("HERE3\n");
			return (NULL);
		}
	}
	else
	{
		if (is_after_great(data->new_command, data->i) && !quotes_after(data->new_command, data->i + get_var_length(&data->new_command[data->i + 1]) - 1))
		{
			printf("bash: $%s: ambiguous redirect\n", data->var_name);
			return (NULL);
		}
		else
			data->new_command = remove_var(data->new_command, data->i);
	}
	free(data->var_name);
	return ((void *)1);
}

void	*look_to_expand(t_expand *data, t_list **env, t_array *array)
{
	if (data->new_command[data->i] == '$' && is_not_after_hdoc(data->new_command, data->i) && !is_in_single_quotes(data->new_command, data->i) && valid_var_first_char(data->new_command[data->i + 1]))
	{
		if (data->new_command[data->i + 1] == '?')
		{
			if (handle_expand_error_code(data, array) == NULL)
			{
				printf("HERE1\n");
				return (NULL);
			}
		}
		else
		{
			if (handle_normal_expand(data, env) == NULL)
			{
				printf("HERE2\n");
				return (NULL);
			}
		}
	}
	else
		data->i++;
	return ((void *)1);
}

char	*expand_word(char *command, t_list **env, t_array *array)
{
	t_expand data;

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

