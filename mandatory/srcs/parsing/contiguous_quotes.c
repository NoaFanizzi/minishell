/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:06:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/05/12 10:28:45 by nbodin           ###   ########lyon.fr   */
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
	joined[size - 2] = D_QUOTE;
	joined[size - 1] = 0;
}

void	go_through_join_next_quotes(char **command, char **joined, size_t i)
{
	size_t	j;

	j = 0;
	while (command[j])
	{
		if (i + 1 == j)
			fusion_quotes(command, joined, i, j);
		else
			joined[j] = ft_strdup(command[j]);
		if (!joined[j])
		{
			//free command
			return ;
		}
		j++;
	}
}

        i
hello "hey""rahh" salut
        j

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
		//free command
		return (NULL);
	}
	go_through_join_next_quotes(command, joined, i);
	if ()
	//free command
	return (joined);
}

void	join_previous_simple(char **command, size_t i);
void	join_next_quotes(char **command, size_t i);
void	join_next_simple(char **command, size_t i);


//dont forget to check if command is NULL or not after the join
char	**contigous_quotes(char **command)
{
	size_t	i;

	i = 0;
	
	while (command[i])
	{
		if (command[i][0] == D_QUOTE || command[i][0] == S_QUOTE)
		{
			// if (i > 0 && (command[i - 1][ft_strlen(command[i - 1]) - 1] == D_QUOTE
			// 	|| command[i - 1][ft_strlen(command[i - 1]) - 1] == S_QUOTE))
			// 	command = join_previous_quotes(command, i);
			if (i > 0 && ft_isspace(command[i - 1][ft_strlen(command[i - 1]) - 1]) == 0)
				//join with the previous
		}
		if (command[i][0] == D_QUOTE || command[i][0] == S_QUOTE)
		{
			if (command[i + 1] && (command[i + 1] == D_QUOTE || command[i + 1] == S_QUOTE))
				command = join_next_quotes(command, i);
			else if (command[i + 1] && ft_isspace(command[i + 1][0]) == 0)
				//join with the next
		}
		i++;
	}
}