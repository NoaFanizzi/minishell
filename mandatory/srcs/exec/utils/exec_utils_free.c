/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:22:04 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/28 22:24:19 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab_length(char **tab, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

int	load_cmd_a(char ***a, t_content *content, char ***cmd, size_t *i)
{
	size_t	len_a;

	len_a = ft_tablen(*a);
	*i = 0;
	while (*i < len_a)
	{
		(*cmd)[*i] = ft_strdup((*a)[*i]); // PROTECTED
		if (!(*cmd)[*i])
		{
			if (content->cmd)
				ft_free_tab(content->cmd);
			content->cmd = NULL;
			content->error_code = 1;
			ft_free_tab_length(*cmd, *i);
			return (0);
		}
		(*i)++;
	}
	return (1);
}

int	load_cmd_tab(char ***a, char ***b, t_content *content, char ***cmd)
{
	size_t	i;
	size_t	j;
	size_t	len_b;

	j = 0;
	len_b = ft_tablen(*b);
	if (load_cmd_a(a, content, cmd, &i) == 0)
		return (0);
	while (j < len_b)
	{
		(*cmd)[i + j] = ft_strdup((*b)[j]); // PROTECTED
		if (!(*cmd)[i + j])
		{
			if (content->cmd)
				ft_free_tab(content->cmd);
			content->cmd = NULL;
			ft_free_tab_length(*cmd, i + j);
			content->error_code = 1;
			return (0);
		}
		j++;
	}
	(*cmd)[i + j] = NULL;
	return (1);
}
