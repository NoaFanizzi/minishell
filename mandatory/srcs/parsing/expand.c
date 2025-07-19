/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:40:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/19 16:53:25 by nbodin           ###   ########lyon.fr   */
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
			free(exp_var);
		}
		else
			new_word[k++] = word[j++];
	}
	new_word[k] = 0;
	return (new_word);
}

int is_not_after_hdoc(const char *cmd, size_t var_index)
{
	size_t i = 0;
	int in_squote = 0;
	int in_dquote = 0;

	while (cmd[i])
	{
		// Handle quote state
		if (!in_dquote && cmd[i] == '\'')
			in_squote = !in_squote;
		else if (!in_squote && cmd[i] == '\"')
			in_dquote = !in_dquote;

		// Detect `<<` only when not inside quotes
		if (!in_squote && !in_dquote && cmd[i] == '<' && cmd[i + 1] == '<')
		{
			i += 2;

			// Skip whitespace
			while (cmd[i] && ft_isspace(cmd[i]))
				i++;

			// Now parse the delimiter token
			in_squote = 0;
			in_dquote = 0;

			while (cmd[i])
			{
				if (i == var_index)
					return 0; // ✅ $ is inside the delimiter

				if (!in_dquote && cmd[i] == '\'')
					in_squote = !in_squote;
				else if (!in_squote && cmd[i] == '"')
					in_dquote = !in_dquote;

				// Unquoted delimiter boundary
				if (!in_squote && !in_dquote &&
					(ft_isspace(cmd[i]) || cmd[i] == '|' ||
					 cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '\0'))
					break;

				i++;
			}
		}
		else
		{
			i++;
		}
	}
	return 1;
}


// int	is_not_after_hdoc(char *command, size_t i)
// {
// 	int	quoted;

// 	quoted = is_var_quoted(command, i);
// 	printf("is_quoted = %d\n", quoted);
// 	skip_till_quote(quoted, command, &i);
// 	if (i > 0)
// 		i--;
// 	printf("i = %zu\n", i);
// 	while (i > 0)
// 	{
// 		if (command[i] == S_QUOTE)
// 		{
// 			i--;
// 			while (i > 0 && command[i] != S_QUOTE)
// 				i--; 
// 			if (i == 0)//to see
// 			{
// 				printf("hdoc = 1\n");
// 				return (1);
// 			}
// 		}
// 		else if (command[i] == D_QUOTE)
// 		{
// 			i--;
// 			while (i > 0 && command[i] != D_QUOTE)
// 				i--; 
// 			if (i == 0)//to see
// 			{
// 				printf("hdoc = 1\n");
// 				return (1);
// 			}
// 		}
// 		else if (ft_isspace(command[i]))
// 		{
// 			i--;
// 			while (i > 0 && ft_isspace(command[i]))
// 				i--;
// 			if (command[i] != '<' && i > 0 && command[i - 1] != '<')
// 			{
// 				printf("hdoc = 1\n");
// 				return (1);
// 			};//not an heredoc
// 		}
// 		else if (command[i] != '<' && command[i - 1] != '<')
// 		{
// 			i -= 2;
// 			while (i > 0 && !ft_isspace(command[i])
// 				&& command[i] != S_QUOTE
// 				&& command[i] != D_QUOTE
// 				&& (command[i] != '<'
// 				&& i > 0 && command[i - 1] != '<'))
// 				i--;
// 		}
// 		else
// 		{
// 			printf("hdoc = 0\n");
// 			return (0);
// 		}
// 	}
// 	printf("hdoc = 0\n");
// 	return (0);
// }


char *remove_var(char *command, size_t i)
{
	size_t j;
	size_t	k;
	char	*new_command;

	j = 0;
	k = 0;
	//printf("i = %zu\n", i);
	new_command = malloc((ft_strlen(command) - get_var_length(&command[i + 1])  + 1) * sizeof(char));
	if (!new_command)
		return (NULL);
	while (command[j] && j != i)
		new_command[j++] = command[k++];
	//printf("j = %zu, 1we are here : %s\n", j, &command[j]);
	k++;
	while (command[k] && valid_var_char(command[k]))
		k++;
	//printf("j = %zu, 2we are here : %s\n", j, &command[j]);
	//printf("new_command1 = %s\n", new_command);
	while (command[k])
	{
		new_command[j++] = command[k++];
		//printf("nc[j] : %c, c[j] : %c\n", new_command[j], command[j]);
	}
	//printf("j = %zu, 3we are here : %s\n", j, &command[j]);
	//printf("new_command2 = %s\n", new_command);
	new_command[j] = 0;
	return (new_command);
}

int is_in_single_quotes(const char *cmd, size_t pos)
{
	int in_squote = 0;
	int in_dquote = 0;
	size_t i = 0;

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

char	*expand_error_code(char *command, size_t i, t_array *array)
{
	size_t	j;
	size_t	k;
	char	*new_cmd;

	j = 0;
	k = 0;
	new_cmd = malloc(ft_strlen(command) * sizeof(char));
	if (!new_cmd)
		return (NULL);
	printf("before\n");
	printf("%d\n", array->p_exit_status);//segfault when accessing this
	printf("after\n");
	while (command[j])
	{
		if (j == i)
		{
			printf("hhhhhhh\n");
			new_cmd[k] = array->p_exit_status + 48;
			k++;
			j += 2;
		}
		else
			new_cmd[k++] = command[j++];
	}
	new_cmd[k] = 0;
	return (new_cmd);
}

char	*expand_word(char *command, t_list **env, t_array *array)
{
	char *var_name;
	size_t	i;
	size_t	true_var_length;
	size_t new_length;

	i = 0;
	true_var_length = 0;
	new_length = 0;
	while (command[i])
	{
		if (command[i] == '$' && is_not_after_hdoc(command, i) && !is_in_single_quotes(command, i) && valid_var_first_char(command[i + 1]))
		{
			if (command[i + 1] == '?')
			{
				printf("here\n");
				command = expand_error_code(command, i , array);
				if (!command)
					return (NULL);
				i++;
			}
			else
			{
				var_name = get_var_name(&command[i + 1]);
				if (!var_name)
					return (NULL);
				printf("var name : %s\n", var_name);
				if (var_exists(var_name, *env))
				{
					printf("found var\n");
					true_var_length = get_true_var_length(var_name, *env);
					new_length = true_var_length + ft_strlen(command) - get_var_length(&command[i + 1]) + 1;
					command = expand_var_in_command(command, i, new_length, var_name, env);
					if (!command)
						return (NULL);
					i += true_var_length;
				}
				else
				{
					printf("got here\n");
					command = remove_var(command, i);
					printf("nc = %s\n", command);
				}
			}
		}
		else
			i++;
	}
	return (command);
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

char *expand(char *command, t_list **env, t_array *array)
{
	char *new_command;
	char *temp;
	int counter = 0;

	new_command = ft_strdup(command);
	if (!new_command)
		return NULL;

	while (1)
	{
		temp = expand_word(new_command, env, array);  // always expand first valid `$`
		if (temp == new_command)  // nothing was expanded, we are done
			break;
		free(new_command);
		new_command = temp;
		counter++;
		if (counter > 1000) // safety guard
		{
			fprintf(stderr, "Error: too many variable expansions (infinite loop?)\n");
			free(new_command);
			return NULL;
		}
	}
	free(command);
	return new_command;
}


