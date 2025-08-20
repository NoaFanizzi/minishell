/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:40:45 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/20 13:54:37 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				ft_bzero(void **s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *memoryBlock, int searchedChar,
						size_t size);
char				*ft_strchr(const char *string, int searchedChar);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
unsigned int		ft_strlcpy(char *dest, char *src, unsigned int size);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *first, char *second, size_t length);
char				*ft_strrchr(const char *string, int searchedChar);
int					ft_lower(int c);
int					ft_toupper(int c);
int					ft_atoi(const char *str);
size_t				ft_atol(const char *str);
void				*ft_memset(void *s, int c, size_t n);
char				*ft_strnstr(const char *str, const char *to_find,
						size_t len);
char				*ft_strdup(const char *s);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_calloc(size_t elementCount, size_t elementSize);
int					ft_atoi(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *str, int fd);
void				ft_putnbr_fd(int n, int fd);
char				**ft_split(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_putendl_fd(char *s, int fd);
char				*ft_itoa(int n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_tolower(int c);
void				*ft_memmove(void *d, const void *s, size_t size);
char				*ft_strchr(const char *string, int searchedChar);
void				*ft_memchr(const void *memoryBlock, int searchedChar,
						size_t size);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_strcmp(char *s1, char *s2);
void				ft_strcat(char *dest, char *src);
void				ft_strcpy(char *dest, char *src);
void				ft_wipe(char **ptr);
char				*ft_strncat(char *dest, const char *src, size_t n);

#endif