/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:39:03 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 20:12:15 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_hdoc_nb(char **command)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (ft_strncmp(command[i], "<<", 2) == 0)
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

void	fill_hdocs(char **command, t_heredocs *hdoc, size_t hdoc_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (command[i])
	{
		if (ft_strncmp(command[i], "<<", 2) == 0)
		{
			if (command[i + 1][0] == S_QUOTE || command[i + 1][0] == D_QUOTE)
				hdoc[j].s_quoted = 1;
			else
				hdoc[j].s_quoted = 0;
			hdoc[j].text = NULL;
			hdoc[j].size = hdoc_count;
			j++;
		}
		i++;
	}
}

int	create_hdoc_struct(char **command, t_content *content, t_array *array)
{
	size_t	hdoc_count;

	hdoc_count = count_hdoc_nb(command);
	if (hdoc_count == 0)
	{
		content->hdoc = NULL;
		return (0);
	}
	content->hdoc = malloc(hdoc_count * sizeof(t_heredocs));
	if (!content->hdoc)
	{
		free(array->content);
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		array->p_exit_status = 1;
		return(1);
	}
	fill_hdocs(command, content->hdoc, hdoc_count);
	return (0);
}
