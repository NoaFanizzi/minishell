/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_file_generation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:04:56 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/25 11:13:08 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_load_temp_file(int random_fd, char **random_file)
{
	char	*temp_file;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < 5)
	{
		i = 0;
		temp_file = get_next_line(random_fd);
		if (!temp_file)
			break ;
		while (temp_file[i] && j < 5)
		{
			if (ft_isalpha(temp_file[i]) == 1)
			{
				(*random_file)[j] = temp_file[i];
				j++;
			}
			i++;
		}
		free(temp_file);
	}
	(*random_file)[5] = '\0';
}

int	ft_get_temp_file(char **random_file, t_content *content)
{
	int	random_fd;

	*random_file = ft_calloc(6, sizeof(char)); // PROTECTED
	if (!*random_file)
		return (ft_open_error(content, "random_file"));
	random_fd = open("/dev/random", O_RDONLY); // PROTECTED
	if (random_fd == -1)
	{
		free(*random_file);
		return (ft_open_error(content, "/dev/random"));
	}
	ft_load_temp_file(random_fd, random_file);
	close(random_fd);
	return (0);
}
