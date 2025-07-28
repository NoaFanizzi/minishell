/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:06:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/28 22:53:13 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
 
int		ft_isspace(char c)
{
	if ((9 <= c && c  <= 13) || (c == 32))
		return (1);
	return (0);
}

void	fusion_quotes_next(char **command, char **joined, size_t i, size_t j)
{
	size_t	size;
	size_t	k;

	k = 0;
	while (joined[k])
		k++;	
	rem_and_shift(command[j]);
	rem_and_shift(command[i]);
	size = ft_strlen(command[j]) + ft_strlen(command[i]) + 3;
	joined[k] = malloc(size * sizeof(char));
	if (!joined[k])
		return ;
	joined[k][0] = D_QUOTE;
	joined[k][1] = 0;
	ft_strlcat(joined[k], command[i], size);
	ft_strlcat(joined[k], command[j], size);
	joined[k][size - 2] = D_QUOTE;
	joined[k][size - 1] = 0;
}

void	go_through_join_next_quotes(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (command[j])
	{
		if (i == j)
		{
			fusion_quotes_next(command, joined, i, j + 1);
			j++;
		}
		else
			joined[k] = ft_strdup(command[j]);
		if (!joined[k])
		{
			free_words(joined);
			joined = NULL;
			return ;
		}
		j++;
		k++;
		joined[k] = 0;
	}
}

char	**join_next_quotes(char **command, size_t i)
{
	size_t	size;
	char **joined;

	size = 0;
	//printf("next_quotes\n");
	while (command[size])
		size++;
	joined = malloc((size + 1) * sizeof(char *));
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	joined[0] = 0;
	go_through_join_next_quotes(command, joined, i);
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	free_words(command);
	return (joined);
}

size_t	len_until_space_forward(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (i);
		i++;
	}
	return (i);
}

size_t	len_until_space_backward(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
		i++;
	while (i > 0)
	{
		if (ft_isspace(str[i - 1]))
			return (count);
		count++;
		i--;
	}
	return (count);
}

void	fusion_simple_next(char **command, char **joined, size_t i, size_t j)
{
	size_t	size;
	size_t	k;

	k = 0;
	while (joined[k])
	{
		//printf("k = %zu\n", k);
		k++;
	}
	rem_and_shift(command[i]);
	size = len_until_space_forward(command[j]) + ft_strlen(command[i]) + 3;
	joined[k] = malloc(size * sizeof(char));
	if (!joined[k])
		return ;
	joined[k][0] = D_QUOTE;
	joined[k][1] = 0;
	ft_strlcat(joined[k], command[i], size);
	ft_strlcat(joined[k], command[j], size);
	joined[k][size - 2] = D_QUOTE;
	joined[k][size - 1] = 0;
	if (len_until_space_forward(command[j]) != ft_strlen(command[j]))
		joined[k + 1] = ft_strdup(&command[j][len_until_space_forward(command[j]) + 1]);
}

int	check_free_joined(char ***joined, size_t *k)
{
	if (!(*joined)[*k])
	{
		free_words(*joined);
		*joined = NULL;
		return (1);
	}
	(*k)++;
	return (0);
}

void	go_through_join_next_simple(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = -1;
	k = 0;
	while (command[++j])
	{
		if (i == j)
		{
			fusion_simple_next(command, joined, i, j + 1);
			if (len_until_space_forward(command[j + 1]) != ft_strlen(command[j + 1]))
			{
				if (check_free_joined(&joined, &k))
					return ;
			}
			j++;
		}
		else
			joined[k] = ft_strdup(command[j]);
		if (check_free_joined(&joined, &k))
			return ;
		joined[k] = 0;
	}
}

char	**join_next_simple(char **command, size_t i)
{
	size_t	size;
	char **joined;

	size = 0;
	//printf("next_simple\n");
	while (command[size])
		size++;
	joined = malloc((size + 1) * sizeof(char *));
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	joined[0] = 0;
	go_through_join_next_simple(command, joined, i);
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	free_words(command);
	return (joined);
}

//PREV

void	fusion_simple_prev(char **command, char **joined, size_t i, size_t j)
{
	size_t	size;
	size_t	k;
	
	k = 0;
	while (joined[k])
		k++;
	rem_and_shift(command[i]);
	size = len_until_space_backward(command[j]) + ft_strlen(command[i]) + 3;
	if (len_until_space_backward(command[j]) != ft_strlen(command[j]))
	{
		joined[k] = ft_substr(command[j], 0, ft_strlen(command[j]) - len_until_space_backward(command[j]));
		if (!joined[k])
			return ;
		k++;
	}
	joined[k] = malloc(size * sizeof(char));
	if (!joined[k])
		return ;
	joined[k][0] = D_QUOTE;
	joined[k][1] = 0;
	ft_strlcat(joined[k], &command[j][ft_strlen(command[j]) - len_until_space_backward(command[j])], size);
	ft_strlcat(joined[k], command[i], size);
	joined[k][size - 2] = D_QUOTE;
	joined[k][size - 1] = 0;
}

void	go_through_join_prev_simple(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = -1;
	k = 0;
	while (command[++j])
	{
		if (i - 1 == j)
		{
			fusion_simple_prev(command, joined, i, j);
			if (len_until_space_backward(command[j]) != ft_strlen(command[j]))
				k++;
			j++;
		}
		else
			joined[k] = ft_strdup(command[j]);
		if (check_free_joined(&joined, &k))
			return ;
		joined[k] = 0;
	}
}


char	**join_prev_simple(char **command, size_t i)
{
	size_t	size;
	char **joined;

	size = 0;
	while (command[size])
		size++;
	joined = malloc((size + 1) * sizeof(char *));
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	joined[0] = 0;
	go_through_join_prev_simple(command, joined, i);
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	free_words(command);
	return (joined);
}

void	fusion_quotes_prev(char **command, char **joined, size_t i, size_t j)
{
	size_t	size;
	size_t	k;
	
	k = 0;
	while (joined[k])
		k++;
	rem_and_shift(command[i]);
	rem_and_shift(command[j]);
	size = ft_strlen(command[j]) + ft_strlen(command[i]) + 3;
	joined[k] = malloc(size * sizeof(char));
	if (!joined[k])
		return ;
	joined[k][0] = D_QUOTE;
	joined[k][1] = 0;
	ft_strlcat(joined[k], command[j], size);
	ft_strlcat(joined[k], command[i], size);
	joined[k][size - 2] = D_QUOTE;
	joined[k][size - 1] = 0;
}

void	go_through_join_prev_quotes(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (command[j])
	{
		if (i - 1 == j)
			fusion_quotes_prev(command, joined, i, j);
		else
			joined[k] = ft_strdup(command[j]);
		if (!joined[k])
		{
			free_words(joined);
			joined = NULL;
			return ;
		}
		if (i - 1 == j)
			j++;
		j++;
		k++;
		joined[k] = 0;
	}
}

char	**join_prev_quotes(char **command, size_t i)
{
	size_t	size;
	char **joined;

	size = 0;
	while (command[size])
		size++;
	joined = malloc((size + 1) * sizeof(char *));
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	joined[0] = 0;
	go_through_join_prev_quotes(command, joined, i);
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	free_words(command);
	return (joined);
}

int		is_not_pipe_redir(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (0);
	return (1);
}

int		is_quote(char c)
{
	if (c == S_QUOTE || c == D_QUOTE)
		return (1);
	return (0);
}

void	shift_words(char **command, size_t i)
{
	while (command[i + 1])
	{
		ft_strcpy(command[i], command[i+1]);
		i++;
	}
	command[i] = 0;
}

int	call_prev_quotes(char **command, char ***cmd, size_t *i, int *merged)
{
	command = join_prev_quotes(command, *i);
	if (!command)
		return (1);
	*cmd = command;
	(*i)--;
	*merged = 1;
	return (0);
}

int	call_prev_simple(char **command, char ***cmd, size_t *i, int *merged)
{
	command = join_prev_simple(command, *i);
	if (!command)
		return (1);
	*cmd = command;
	(*i)--;
	*merged = 1;
	return (0);
}

int	call_next_quotes(char **command, char ***cmd, size_t i, int *merged)
{
	command = join_next_quotes(command, i);
	if (!command)
		return (1);
	*cmd = command;
	*merged = 1;
	return (0);
}

int call_next_simple(char **command, char ***cmd, size_t *i, int *merged)
{
	command = join_next_simple(command, *i);
	if (!command)
		return (1);
	*cmd = command;
	*merged = 1;
	(*i)++;
	return (0);
}

int	call_join_prev(char **command, char ***cmd, size_t *i, int *merged)
{
	if (*i > 0 && command[*i - 1] && ft_strlen(command[*i - 1]) > 0
		&& is_quote(command[*i - 1][ft_strlen(command[*i - 1]) - 1]))
	{
		if (call_prev_quotes(command, cmd, i, merged))
			return (1);
	}
	else if (*i > 0 && command[*i - 1] && ft_strlen(command[*i - 1]) > 0
		&& (ft_isspace(command[*i - 1][ft_strlen(command[*i - 1]) - 1]) == 0)
		&& is_not_pipe_redir(command[*i - 1][ft_strlen(command[*i - 1]) - 1]))
	{
		if (call_prev_simple(command, cmd, i, merged))
			return (1);
	}
	return (0);
}

int	call_join_next_prev(char **command, char ***cmd, size_t *i, int *merged)
{
	if (call_join_prev(command, cmd, i, merged))
		return (1);
	else if (command[*i + 1] && is_quote(command[*i + 1][0]))
	{
		if (call_next_quotes(command, cmd, *i, merged))
			return (1);
		return (0);
	}
	else if (command[*i + 1] && (ft_isspace(command[*i + 1][0]) == 0)
		&& is_not_pipe_redir(command[*i + 1][0]))
	{
		if (call_next_simple(command, cmd, i, merged))
			return (1);
	}
	return (0);
}

void	contiguous_quotes(char ***cmd)
{
	size_t	i;
	char	**command;
	int		merged;

	i = 0;
	command = *cmd;
	while (command[i])
	{
		merged = 0;
		if (is_quote(command[i][0]))
		{
			if (call_join_next_prev(command, cmd, &i, &merged))
				return ;
			command = *cmd; // **ensure we work on the updated pointer**
		}
		if (merged == 0)
			i++;
		else
			continue; // **RECHECK same index after a merge**
	}
}
