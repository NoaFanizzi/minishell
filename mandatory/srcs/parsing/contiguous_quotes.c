/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:06:12 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/05 10:40:00 by nofanizz         ###   ########.fr       */
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

void	go_through_join_next_simple(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (command[j])
	{
		if (i == j)
		{
			fusion_simple_next(command, joined, i, j + 1);
			if (len_until_space_forward(command[j + 1]) != ft_strlen(command[j + 1]))
			{
				if (!joined[k])
				{
					free_words(joined);
					joined = NULL;
					return ;
				}
				k++;
			}
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
	// printf("cmdi : %s\n", command[i]);
	// printf("cmdj : %s\n", command[j]);
	// printf("size : %zu\n", size);
	// printf("size2 : %zu\n", len_until_space_forward(command[j]) + 1);
	// printf("normal len : %zu\n", ft_strlen(command[j]));
	if (len_until_space_backward(command[j]) != ft_strlen(command[j]))
	{
		joined[k] = ft_substr(command[j], 0, ft_strlen(command[j]) - len_until_space_backward(command[j]));
		if (!joined[k])
			return ;
		k++;
	}
	// printf("cmdi : %s\n", command[i]);
	// printf("cmdj : %s\n", command[j]);
	// printf("size : %zu\n", size);
	// printf("size2 : %zu\n", len_until_space_forward(command[j]) + 1);
	// printf("K = %zu\n", k);
	joined[k] = malloc(size * sizeof(char));
	if (!joined[k])
		return ;
	joined[k][0] = D_QUOTE;
	joined[k][1] = 0;
	//printf("%zu\n", len_until_space_backward(command[j]));
	//printf("before strlcat : %s\n", joined[k]);
	ft_strlcat(joined[k], &command[j][ft_strlen(command[j]) - len_until_space_backward(command[j])], size);
	//printf("first strlcat : %s\n", joined[k]);
	ft_strlcat(joined[k], command[i], size);
	// printf("second strlcat : %s\n", joined[k]);
	joined[k][size - 2] = D_QUOTE;
	joined[k][size - 1] = 0;
	// printf("final result : %s\n", joined[k]);
	// printf("cat part : %s\n", joined[k - 1]);
}

void	go_through_join_prev_simple(char **command, char **joined, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (command[j])
	{
		// printf("YAAA\n");
		if (i - 1 == j)
		{
			fusion_simple_prev(command, joined, i, j);
			if (len_until_space_backward(command[j]) != ft_strlen(command[j]))
				k++;
			j++;
			// printf("final result : %s\n", joined[k]);
			// printf("cat part : %s\n", joined[k - 1]);
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
		// printf("J = %zu\n", j);
		// printf("K2 = %zu\n", k);
		joined[k] = 0;
		// printf("%s\n", joined[0]);
		// printf("%s\n", joined[1]);
		// printf("%s\n", joined[2]);
	}
}


char	**join_prev_simple(char **command, size_t i)
{
	size_t	size;
	char **joined;

	size = 0;
	//printf("prev_simple\n");
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
	//printf("prev_quotes\n");
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


//maybe make a copy of command to not modify and iterate at the same time,
//and also to free command before returning the new command

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

void	contiguous_quotes(char ***cmd)
{
	size_t	i;
	char	**command;

	i = 0;
	command = *cmd;
	while (command[i])
	{
		//printf("checking command[%zu] = [%s], first char = [%c] (ascii: %d)\n", i, command[i], command[i][0], command[i][0]);
		if (is_quote(command[i][0]))
		{
			if (i > 0 && command[i - 1] && ft_strlen(command[i - 1]) > 0 && is_quote(command[i - 1][ft_strlen(command[i - 1]) - 1]))
			{
				//printf("prev_quotes\n");
				command = join_prev_quotes(command, i);
				if (!command)
				return ;
				*cmd = command;
				i--;
			}
			else if (i > 0 && command[i - 1] && ft_strlen(command[i - 1]) > 0 && (ft_isspace(command[i - 1][ft_strlen(command[i - 1]) - 1]) == 0) && is_not_pipe_redir(command[i - 1][ft_strlen(command[i - 1]) - 1]))
			{
				//printf("prev_simple\n");
				command = join_prev_simple(command, i);
				if (!command)
				return ;
				*cmd = command;
				//if (command && command[i - 1] && (len_until_space_backward(command[i - 1]) == ft_strlen(command[i - 1])))
					i--;
			}
			else if (command[i + 1] && is_quote(command[i + 1][0]))
			{
				//printf("next_quotes\n");
				command = join_next_quotes(command, i);
				if (!command)
					return ;
				*cmd = command;
			}
			else if (command[i + 1] && (ft_isspace(command[i + 1][0]) == 0) && is_not_pipe_redir(command[i + 1][0]))
			{
				//printf("next_simple\n");
				command = join_next_simple(command, i);
				if (!command)
				return ;
				//shift_words(command, i + 1);
				*cmd = command;
			}
		}
		i++;
	}
	int k = 0;
	while (command[k])
	{
		//printf("Bword n%d : %s\n", k + 1, command[k]);
		k++;
	}
	//printf("\n\n");
}



// command

//  i
// [e]["ch"][o][ test][0]

//       i
// [e]["ch"][o][ test][0]

//         i
// ["ech"][o][ test][0]

// ["ech"][o][ test][0]
// next
// ["echo"][ test][0]