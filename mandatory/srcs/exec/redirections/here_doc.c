/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:25:47 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/23 17:35:57 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int loop_hdoc(t_array *array, size_t size, size_t i)
{
	size_t	j;
	int returned_value;

	j = 0;
	while(j < size)
	{
		if(array->content[i].files[j].type == HDOC)
		{
			signal(SIGINT, deal_with_sigint_hdoc);
			returned_value = ft_deal_with_hdoc(&array->content[i], &j);
			signal(SIGINT, deal_with_sigint);
		}
		if(returned_value == O_ERROR || returned_value == 1)
		{
			printf("going to return\n");
			return(1);
		}
		j++;
	}
    return(0);
}

int	ft_process_here_doc(t_array *array)
{
	int	i;
	size_t	size;

	i = 0;
	while(i < array->size)
	{
		if(array->content[i].hdoc)
		{
			size = array->content[i].files[0].size;
			if(loop_hdoc(array, size, i) == 1)
			{
				printf("ft_process_here_doc\n");
				array->p_exit_status = 1;
				return(1);
			}
		}
		i++;
	}
	return(0);
}
