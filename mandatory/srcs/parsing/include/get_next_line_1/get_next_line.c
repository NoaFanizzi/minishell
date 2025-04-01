/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:05:10 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/01 17:05:25 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static char	*ft_free_and_return_null(char **ptr1, char **ptr2)
{
	ft_free_ptr((void **)ptr1);
	ft_free_ptr((void **)ptr2);
	return (NULL);
}

static char	*ft_read(int fd, char *reserve)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		ft_free_ptr((void **)&reserve);
		return (NULL);
	}
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (ft_free_and_return_null(&buffer, &reserve));
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		reserve = ft_strjoin(reserve, buffer);
		if (!reserve)
			return (ft_free_ptr((void **)&buffer));
		if (ft_strchr(reserve, '\n'))
			break ;
	}
	ft_free_ptr((void **)&buffer);
	return (reserve);
}

static char	*ft_extract_line(char *reserve)
{
	char	*line;
	int		i;

	if (!reserve || !reserve[0])
		return (NULL);
	i = 0;
	while (reserve[i] && reserve[i] != '\n')
		i++;
	line = ft_substr(reserve, 0, i + 1);
	return (line);
}

static char	*ft_update_reserve(char *reserve)
{
	char	*new_reserve;
	int		i;

	i = 0;
	while (reserve[i] && reserve[i] != '\n')
		i++;
	if (!reserve[i])
		ft_free_ptr((void **)&reserve);
	new_reserve = ft_substr(reserve, i + 1, ft_strlen(reserve) - i);
	ft_free_ptr((void **)&reserve);
	return (new_reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*line;

	reserve = ft_read(fd, reserve);
	if (!reserve)
		return (NULL);
	line = ft_extract_line(reserve);
	if (!line)
		return (ft_free_ptr((void **)&reserve));
	reserve = ft_update_reserve(reserve);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main(int argc, char **argv)
// {
//     int     fd;
//     char    *line;

//     if (argc < 2)
//     {
//         printf("Usage: %s <filename>\n", argv[0]);
//         return (EXIT_FAILURE);
//     }
//     fd = open(argv[1], O_RDONLY);
// 	// fd = 0;
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (EXIT_FAILURE);
//     }
//     while ((line = get_next_line(fd)))
//     {
//         printf("%s", line);
//         free(line);
//     }
// 	printf("%s", line);
//     free(line);
//     close(fd);

//     return (EXIT_SUCCESS);
// }