/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:46:20 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 22:11:58 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_meta_count(char **command, const char *charset)
{
	int		count;
	size_t	i;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (command[i][0] == D_QUOTE || command[i][0] == S_QUOTE)
			count++;
		else
			count += twisted_count_words(command[i], charset);
		i++;
	}
	return (count);
}

char	**twisted_fill_splitted(const char *s, const char *charset,
		char **splitted, size_t *j)
{
	static int	tab[2] = {0, 0};

	// Reset static variables for each new string
	tab[0] = 0;
	tab[1] = 0;
	while (s[tab[0]])
	{
		tab[0] = tab[1];
		if (is_sep(s[tab[1]], charset))
		{
			while (s[tab[1]] && is_sep(s[tab[1]], charset))
			{
				if (++tab[1] && s[tab[1]] && is_sep(s[tab[1]], charset)
					&& s[tab[1] - 1] != s[tab[1]])
					break ;
			}
		}
		else
		{
			while (s[tab[1]] && !is_sep(s[tab[1]], charset))
				tab[1]++;
		}
		if (add_segment(s, &splitted, j, tab) == 1)
			return (free_words(splitted));
		if (!splitted)
			return (NULL);
	}
	return (splitted);
}

char	**fill_meta_words(char **splitted, char **command, const char *charset)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (command[k])
	{
		if (command[k][0] == D_QUOTE || command[k][0] == S_QUOTE)
		{
			// Copy quoted strings as-is (they shouldn't be split by metacharacters)
			splitted[i] = ft_strdup(command[k]); // PROTECTED
			if (!splitted[i])
				return (free_words(splitted));
			i++;
		}
		else
		{
			// Split non-quoted strings by metacharacters
			if (!twisted_fill_splitted(command[k], charset, splitted, &i))
				return (NULL);
		}
		k++;
	}
	splitted[i] = 0;
	return (splitted);
}

char	**meta_splitting(char **command)
{
	char		**splitted;
	int			count;
	const char	charset[4] = {'>', '<', '|', 0};

	count = split_meta_count(command, charset);
	splitted = malloc((count + 1) * sizeof(char *)); // PROTECTED
	if (!splitted)
	{
		printf("la\n");
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (free_words(command));
	}
	splitted = fill_meta_words(splitted, command, charset);
	free_words(command);
	if (!splitted)
	{
		printf("slt\n");
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (NULL);
	}
	return (splitted);
}
