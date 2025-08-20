/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:48:41 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/20 15:49:10 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin_free(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*merged;

	if (!s1)
		return (ft_strdup(s2));
	merged = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!merged)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		merged[i] = s1[i];
	j = -1;
	while (s2[++j])
	{
		merged[i] = s2[j];
		i++;
	}
	free(s1);
	return (merged);
}

static char	*ft_parse(char *buffer, int fd)
{
	int		length;
	char	*line;

	line = NULL;
	if (ft_strlen(buffer) > 0)
	{
		line = ft_strdup(buffer);
		if (!line)
			return (NULL);
	}
	while (!ft_strchr(buffer, '\n'))
	{
		length = read(fd, buffer, BUFFER_SIZE);
		if (length < 0)
		{
			if (line)
				free(line);
			return (NULL);
		}
		if (length == 0)
			return (line);
		buffer[length] = 0;
		line = ft_strjoin_free(line, buffer);
	}
	return (line);
}

static void	ft_get_remainders(char *remainders)
{
	size_t	i;
	size_t	j;

	j = gnl_ft_strchr(remainders, '\n');
	if (!j)
	{
		remainders[0] = 0;
		return ;
	}
	i = 0;
	while (remainders[j + i])
	{
		remainders[i] = remainders[i + j];
		i++;
	}
	remainders[i] = 0;
}

static char	*ft_get_line(char *line)
{
	size_t	i;
	size_t	len;
	char	*res;

	len = gnl_ft_strchr(line, '\n');
	if (!len)
		return (line);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (free(line), NULL);
	i = 0;
	while (i < len)
	{
		res[i] = line[i];
		i++;
	}
	return (free(line), res);
}

char	*get_next_line(int fd)
{
	static char	remainders[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_parse(remainders, fd);
	ft_get_remainders(remainders);
	line = ft_get_line(line);
	return (line);
}
