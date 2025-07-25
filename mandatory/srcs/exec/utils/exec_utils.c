/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:17:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/25 11:55:56 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ct_get_paths(t_list *var, t_content *content)
{
	char	**options;
	t_env	*cpy;

	options = NULL;
	if (!var)
		return (NULL);
	cpy = get_env("PATH", var);
	if (cpy == NULL)
		return (NULL);
	options = ft_split(cpy->arg, ':');
	if (!options)
		ft_exit(content);
	if (!options[0])
	{
		free(options);
		options = NULL;
	}
	return (options);
}

char	**ft_cmd_join(char **a, char **b)
{
	size_t	i;
	size_t	j;
	size_t	length;
	char	**cmd;

	i = 0;
	j = 0;
	length = ft_tablen(a) + ft_tablen(b);
	cmd = ft_calloc(length + 1, (sizeof(char *)));
	while (i < ft_tablen(a))
	{
		cmd[i] = ft_strdup(a[i]);
		i++;
	}
	while (j < ft_tablen(b))
	{
		cmd[i] = ft_strdup(b[j]);
		i++;
		j++;
	}
	if (a)
		ft_free_tab(a);
	if (b)
		ft_free_tab(b);
	return (cmd);
}

void	ft_display_array_content(t_array *array)
{
	int	i;

	i = 0;
	while (i < array->size)
	{
		printf("content[%d] : \n\n", i);
		printf("-----cmd-----|\n");
		ft_display_tab(array->content[i].cmd);
		printf("-------------|\n\n");
		if (array->content[i].arg[0])
		{
			printf("-----args----|\n");
			ft_display_tab(array->content[i].arg);
			printf("-------------|\n\n");
		}
		i++;
	}
}

int	ft_contains_dir(t_content *content)
{
	if ((content->cmd[0][0] == '/')
		|| (ft_strncmp(content->cmd[0], "./", 2) == 0)
		|| (ft_strncmp(content->cmd[0], "../", 3) == 0)
		|| (ft_strcmp(content->cmd[0], "..") == 0)
		|| (ft_strcmp(content->cmd[0], ".") == 0)
		|| (content->cmd[0][1] == '/'))
		return (1);
	return (0);
}
