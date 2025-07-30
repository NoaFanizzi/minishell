/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:13:37 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/24 17:01:35 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return (1);
	if (!lst)
		return (1);
	if (!*lst)
	{
		*lst = new;
		return (0);
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
	return (0);
}
