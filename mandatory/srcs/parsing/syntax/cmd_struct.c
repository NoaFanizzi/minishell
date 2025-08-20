/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:13:15 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/20 15:47:08 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	figure_in_out_files(char **cmd, t_content *content)
{
	size_t	redir_count;
	int		tab[2];

	tab[0] = 0;
	tab[1] = 0;
	redir_count = count_redir(cmd);
	content->redir_count = redir_count;
	content->files = NULL;
	if (redir_count == 0)
		return (0);
	content->files = ft_calloc((redir_count + 1), sizeof(t_files));
	if (!content->files)
		return (1);
	while (cmd[tab[0]])
	{
		if (check_for_op(cmd, content, tab, redir_count))
		{
			free(content->files);
			content->files = NULL;
			return (1);
		}
	}
	if (tab[1] == 0)
		content->files = NULL;
	return (0);
}

int	free_in_out_files(t_content *content, t_array *array)
{
	free(content->hdoc);
	free(array->content);
	ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
	array->p_exit_status = 1;
	return (1);
}

int	free_cmd_opt(t_content *content, t_array *array)
{
	free(content->hdoc);
	free(content->files);
	free(array->content);
	ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
	array->p_exit_status = 1;
	return (1);
}

int	free_arg(t_content *content, t_array *array)
{
	free(content->hdoc);
	free(content->files);
	free_words(content->cmd);
	free(array->content);
	ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
	array->p_exit_status = 1;
	return (1);
}

int	create_cmd_struct(char ***cmd_splitted, t_content *content,
		size_t cmd_index, t_array *array)
{
	if (figure_in_out_files(cmd_splitted[cmd_index], content))
		return (free_in_out_files(content, array));
	if (identify_cmd_opt(cmd_splitted[cmd_index], content))
		return (free_cmd_opt(content, array));
	if (identify_arg(cmd_splitted[cmd_index], content))
		return (free_arg(content, array));
	content->pos = cmd_index;
	content->cmd_splitted = cmd_splitted;
	return (0);
}
