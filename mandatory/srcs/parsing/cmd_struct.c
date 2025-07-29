/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:13:15 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 02:22:35 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	figure_in_out_files(char **cmd, t_content *content)
{
	size_t	redir_count;
	int		tab[2];

	tab[0] = 0;
	tab[1] = 1;
	redir_count = count_redir(cmd);
	content->redir_count = redir_count;
	content->files = NULL;
	if (redir_count == 0)
		return ;
	content->files = ft_calloc((redir_count + 1), sizeof(t_files));
	if (!content->files)
		return ;
	while (cmd[tab[0]])
		check_for_op(cmd, content, tab, redir_count);
	if (tab[1] == 0)
		content->files = NULL;
}

void	create_cmd_struct(char ***cmd_splitted, t_content *content,
		size_t cmd_index)
{
	figure_in_out_files(cmd_splitted[cmd_index], content);
	identify_cmd_opt(cmd_splitted[cmd_index], content);
	identify_arg(cmd_splitted[cmd_index], content);
	content->pos = cmd_index;
	content->cmd_splitted = cmd_splitted;
}
