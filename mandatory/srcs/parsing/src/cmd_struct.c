/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:13:15 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/30 17:49:11 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"



size_t	count_redir(char **cmd)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (strncmp(cmd[i], "<", 1) == 0
			|| strncmp(cmd[i], ">", 1) == 0)
			count++;
		i++;
	}
	return (count);
}

//only valid input to read from is the rightmost one,
//only place where the output is going is the rightmost one
//altough there is nothing going in inbetween files when outputing, they are created
//that is not the case for inputs, if they dont exist they are not created
//also output files are created although the command doesnt work
void	figure_in_out_files(char **cmd, t_content *content)
{
	size_t	redir_count;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	redir_count = count_redir(cmd);
	content->files = NULL;
	content->files = malloc(redir_count * sizeof(t_files));
	if (!content->files)
		return ;
	while (cmd[i])
	{
		if (strncmp(cmd[i], "<<", 2) == 0)
		{
			content->files[j].type = HDOC;
			content->files[j].index = i;
			j++;
		}
		else if (strncmp(cmd[i], ">>", 2) == 0)
		{
			content->files[j].type = APND;
			content->files[j].index = i;
			j++;
		}
		else if (strncmp(cmd[i], "<", 1) == 0)
		{
			content->files[j].type = IN;
			content->files[j].index = i;
			j++;
		}
		else if (strncmp(cmd[i], ">", 1) == 0)
		{
			content->files[j].type = OUT;
			content->files[j].index = i;
			j++;
		}
		i++;
	}
}

void	create_cmd_struct(char ***cmd_splitted, t_content *content, size_t cmd_index)
{
	figure_in_out_files(cmd_splitted[cmd_index], content);
	// identify_cmds(&cmd_splitted[cmd_index]);
	// identify_cmd_opt(&cmd_splitted[cmd_index]);
	// identify_args(&cmd_splitted[cmd_index]);
}