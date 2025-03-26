/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:04:02 by nofanizz          #+#    #+#             */
/*   Updated: 2024/11/12 11:15:11 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*temp;
	t_list	*first;
	t_list	*new;

	first = NULL;
	if (!f || !del)
		return (NULL);
	while (lst)
	{
		temp = f(lst->content);
		if (!temp)
			return (ft_lstclear(&first, del), NULL);
		new = ft_lstnew(temp);
		if (!new)
		{
			del(temp);
			return (ft_lstclear(&first, del), NULL);
		}
		ft_lstadd_back(&first, new);
		lst = lst->next;
	}
	return (first);
}
