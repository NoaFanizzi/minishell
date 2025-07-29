/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:39:03 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 02:28:18 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_hdoc(char **command)
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

int	create_hdoc_struct(char **command, t_content *content)
{
	size_t	hdoc_count;

	hdoc_count = count_hdoc(command);
	if (hdoc_count == 0)
		return (content->hdoc = NULL, 0);
	content->hdoc = malloc(hdoc_count * sizeof(t_heredocs));
	if (!content->hdoc)
		return (-1);
	fill_hdocs(command, content->hdoc, hdoc_count);
	return (0);
}
