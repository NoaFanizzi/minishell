/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:23:15 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 02:22:47 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	figure_hdoc(char **cmd, t_content *content, int tab[2],
		size_t redir_count)
{
	content->files[tab[1]].type = HDOC;
	content->files[tab[1]].index = tab[0];
	content->files[tab[1]].size = redir_count;
	rem_and_shift(cmd[tab[0] + 1]);
	content->files[tab[1]].eof = ft_strdup(cmd[tab[0] + 1]);
	tab[1]++;
	tab[0]++;
}

void	figure_append(char **cmd, t_content *content, int tab[2],
		size_t redir_count)
{
	content->files[tab[1]].type = APND;
	content->files[tab[1]].index = tab[0];
	content->files[tab[1]].size = redir_count;
	content->files[tab[1]].eof = NULL;
	rem_and_shift(cmd[tab[0] + 1]);
	tab[1]++;
	tab[0]++;
}

void	figure_in(char **cmd, t_content *content, int tab[2],
		size_t redir_count)
{
	content->files[tab[1]].type = IN;
	content->files[tab[1]].index = tab[0];
	content->files[tab[1]].size = redir_count;
	content->files[tab[1]].eof = NULL;
	rem_and_shift(cmd[tab[0] + 1]);
	tab[1]++;
	tab[0]++;
}

void	figure_out(char **cmd, t_content *content, int tab[2],
		size_t redir_count)
{
	content->files[tab[1]].type = OUT;
	content->files[tab[1]].index = tab[0];
	content->files[tab[1]].size = redir_count;
	content->files[tab[1]].eof = NULL;
	rem_and_shift(cmd[tab[0] + 1]);
	tab[1]++;
	tab[0]++;
}

void	check_for_op(char **cmd, t_content *content, int tab[2],
		size_t redir_count)
{
	if (strncmp(cmd[tab[0]], "<<", 2) == 0)
		figure_hdoc(cmd, content, tab, redir_count);
	else if (strncmp(cmd[tab[0]], ">>", 2) == 0)
		figure_append(cmd, content, tab, redir_count);
	else if (strncmp(cmd[tab[0]], "<", 1) == 0)
		figure_in(cmd, content, tab, redir_count);
	else if (strncmp(cmd[tab[0]], ">", 1) == 0)
		figure_out(cmd, content, tab, redir_count);
	else
		tab[0]++;
}
