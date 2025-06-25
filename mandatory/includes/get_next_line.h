/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:40:45 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/25 11:00:06 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 18
# endif

char	*get_next_line(int fd);
char	*gnl_ft_strdup(const char *s);
size_t	gnl_ft_strlen(const char *str);
void	gnl_ft_bzero(void *s, size_t n);
void	*gnl_ft_calloc(size_t elementCount, size_t elementSize);
int		gnl_ft_strchr(char *str, char c);

#endif