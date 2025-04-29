/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:13:15 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/29 17:28:14 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"


void	figure_pipes_com(char ***cmd_splitted, t_content **content, size_t cmd_index)
{
	if (cmd_index > 0 && strncmp(cmd_splitted[cmd_index - 1], "|", 1) == 0)
		(*content)->input = PIPE;
	else
		(*content)->input = STDIN;
	if (cmd_splitted[cmd_index + 1] != 0 && strncmp(cmd_splitted[cmd_index + 1], "|", 1) == 0)
		(*content)->output = PIPE;
	else
		(*content)->output = STDOUT;
}

//only valid input to read from is the rightmost one,
//only place where the output is going is the rightmost one
//altough there is nothing going in inbetween files when outputing, they are created
//that is not the case for inputs, if they dont exist they are not created
//also output files are created although the command doesnt work
void	figure_int_out_files(char **cmd, t_content **content, size_t cmd_index)
{
	if (is_there_red_out())
	{
		find_last_red_out();
		(*content)->output
	}

	
}

void	create_cmd_struct(char ***cmd_splitted, t_content **content, size_t cmd_index)
{
	figure_pipes_com(cmd_splitted, content, cmd_index);
	figure_in_out_files(&cmd_splitted[cmd_index], content, cmd_index);
	identify_cmds(&cmd_splitted[cmd_index]);
	identify_cmd_opt(&cmd_splitted[cmd_index]);
	identify_args(&cmd_splitted[cmd_index]);
}