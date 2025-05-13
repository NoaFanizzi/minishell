/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:06:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/05/13 10:12:50 by nbodin           ###   ########lyon.fr   */
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
	
	rem_and_shift(command[j]);
	rem_and_shift(command[i]);
	size = ft_strlen(command[j]) + ft_strlen(command[i]) + 3;
	joined[i] = malloc(size * sizeof(char));
	if (!joined[i])
		return ;
	joined[i][0] = D_QUOTE;
	joined[i][1] = 0;
	strlcat(joined[i], command[i], sizeof(joined[i]));
	strlcat(joined[i], command[j], sizeof(joined[i]));
	joined[i][size - 2] = D_QUOTE;
	joined[i][size - 1] = 0;
}

void	go_through_join_next_quotes(char **command, char **joined, size_t i)
{
	size_t	j;

	j = 0;
	while (command[j])
	{
		if (i == j)
			fusion_quotes_next(command, joined, i, j + 1);
		else
			joined[j] = ft_strdup(command[j]);
		if (!joined[j])
		{
			free_words(joined);
			joined = NULL;
			return ;
		}
		j++;
	}
}

char	**join_next_quotes(char **command, size_t i)
{
	size_t	size;
	char **joined;

	size = 0;
	while (command[size])
		size++;
	joined = malloc(size * sizeof(char *));
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	go_through_join_next_quotes(command, joined, i);
	free_words(command);
	return (joined);
}

void	fusion_simple_next(char **command, char **joined, size_t i, size_t j)
{
	size_t	size;
	
	rem_and_shift(command[i]);
	size = ft_strlen(command[j]) + ft_strlen(command[i]) + 3;
	joined[i] = malloc(size * sizeof(char));
	if (!joined[i])
		return ;
	joined[i][0] = D_QUOTE;
	joined[i][1] = 0;
	strlcat(joined[i], command[i], sizeof(joined[i]));
	strlcat(joined[i], command[j], sizeof(joined[i]));
	joined[i][size - 2] = D_QUOTE;
	joined[i][size - 1] = 0;
}
		
void	go_through_join_next_simple(char **command, char **joined, size_t i)
{
	size_t	j;

	j = 0;
	while (command[j])
	{
		if (i == j)
			fusion_simple_next(command, joined, i, j + 1);
		else
			joined[j] = ft_strdup(command[j]);
		if (!joined[j])
		{
			free_words(joined);
			joined = NULL;
			return ;
		}
		j++;
	}
}

char	**join_next_simple(char **command, size_t i)
{
	size_t	size;
	char **joined;

	size = 0;
	while (command[size])
		size++;
	joined = malloc(size * sizeof(char *));
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	go_through_join_next_simple(command, joined, i);
	free_words(command);
	return (joined);
}

void	fusion_simple_prev(char **command, char **joined, size_t i, size_t j)
{
	size_t	size;
	
	rem_and_shift(command[i]);
	size = ft_strlen(command[j]) + ft_strlen(command[i]) + 3;
	joined[j] = malloc(size * sizeof(char));
	if (!joined[j])
		return ;
	joined[j][0] = D_QUOTE;
	joined[j][1] = 0;
	strlcat(joined[j], command[j], sizeof(joined[i]));
	strlcat(joined[j], command[i], sizeof(joined[i]));
	joined[j][size - 2] = D_QUOTE;
	joined[j][size - 1] = 0;
}

void	go_through_join_prev_simple(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (command[j])
	{
		if (i - 1 == j)
			fusion_simple_prev(command, joined, i, j);
		else
			joined[j] = ft_strdup(command[j]);
		if (!joined[j])
		{
			free_words(joined);
			joined = NULL;
			return ;
		}
		if (i - 1 == j)
			j++;
		j++;
	}
}
j    j
e"ch"o test

j
[ech] [] [] []

char	**join_prev_simple(char **command, size_t i)
{
	size_t	size;
	char **joined;

	size = 0;
	while (command[size])
		size++;
	joined = malloc(size * sizeof(char *));
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	go_through_join_prev_simple(command, joined, i);
	free_words(command);
	return (joined);
}





void	fusion_quotes_prev(char **command, char **joined, size_t i, size_t j)
{
	size_t	size;
	
	rem_and_shift(command[i]);
	rem_and_shift(command[j]);
	size = ft_strlen(command[j]) + ft_strlen(command[i]) + 3;
	joined[j] = malloc(size * sizeof(char));
	if (!joined[j])
		return ;
	joined[j][0] = D_QUOTE;
	joined[j][1] = 0;
	strlcat(joined[j], command[j], sizeof(joined[i]));
	strlcat(joined[j], command[i], sizeof(joined[i]));
	joined[j][size - 2] = D_QUOTE;
	joined[j][size - 1] = 0;
}

void	go_through_join_prev_quotes(char **command, char **joined, size_t i)
{
	size_t	j;

	j = 0;
	while (command[j])
	{
		if (i - 1 == j)
			fusion_quotes_prev(command, joined, i, j);
		else
			joined[j] = ft_strdup(command[j]);
		if (!joined[j])
		{
			free_words(joined);
			joined = NULL;
			return ;
		}
		if (i - 1 == j)
			j++;
		j++;
	}
}

char	**join_prev_quotes(char **command, size_t i)
{
	size_t	size;
	char **joined;

	size = 0;
	while (command[size])
		size++;
	joined = malloc(size * sizeof(char *));
	if (!joined)
	{
		free_words(command);
		return (NULL);
	}
	go_through_join_prev_quotes(command, joined, i);
	free_words(command);
	return (joined);
}






// char **duplicate_command(char **command)
// {
// 	size_t	i;
// 	char **new_cmd;

// 	i = 0;
// 	while (command[i])
// 		i++;
// 	new_cmd = malloc((i + 1) * sizeof(char *));
// 	if (!new_cmd)
// 		return (NULL);
// 	i = 0;
// 	while (command[i])
// 	{
// 		new_cmd[i] = ft_strdup(command[i]);
// 		if (!new_cmd[i])
// 		{
// 			free_words(new_cmd);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	return (new_cmd);
// }

   i
e"ch"o test

ech 

//maybe make a copy of command to not modify and iterate at the same time,
//and also to free command before returning the new command
char	**contiguous_quotes(char **command)
{
	size_t	i;
	// char **new_cmd;
	
	// new_cmd = duplicate_command(command);
	// if (!new_cmd)
	// 	return (NULL);
	i = 0;
	while (command[i])
	{
		if (command[i][0] == D_QUOTE || command[i][0] == S_QUOTE)
		{
			if (i > 0)
			{
				if(ft_isspace(command[i - 1][ft_strlen(command[i - 1]) - 1]) == 0)
					command = join_prev_simple(command, i);
				else if (command[i - 1][ft_strlen(command[i - 1]) - 1] == D_QUOTE
				 	|| command[i - 1][ft_strlen(command[i - 1]) - 1] == S_QUOTE)
					command = join_prev_quotes(command, i);
				if (!command)
					return (NULL);
			}
			else if (command[i + 1])
			{
				if (command[i + 1][0] == D_QUOTE || command[i + 1][0] == S_QUOTE)
					command = join_next_quotes(command, i);
				else if (ft_isspace(command[i + 1][0]) == 0)
					command = join_next_simple(command, i);
				i++;
				if (!command)
					return (NULL);
			}
		}
		else
			i++;
	}
	return (command);
}
