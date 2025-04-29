/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:13:15 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/29 10:29:34 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"


void	figure_pipes_com(char ***cmd_splitted, size_t cmd_index, t_content **cmd_struct)
{
	if (cmd_index > 0 && strncmp(cmd_splitted[cmd_index - 1], "|", 1) == 0)
		(*cmd_struct)->from_pipe = 1;
	else
		(*cmd_struct)->from_pipe = 0;
	if (cmd_splitted[cmd_index + 1] != 0 && strncmp(cmd_splitted[cmd_index + 1], "|", 1) == 0)
		(*cmd_struct)->to_pipe = 1;
	else
		(*cmd_struct)->to_pipe = 0;
}

//only valid input to read from is the rightmost one,
//only place where the output is going is the rightmost one
//altough there is nothing going in inbetween files when outputing, they are created
//that is not the case for inputs, if they dont exist they are not created
//also output files are created although the command doesnt work
void	figure_int_out_files(char **cmd, t_content **cmd_struct)
{
	
}

void	create_cmd_struct(char ***cmd_splitted, size_t cmd_index, t_content **cmd_struct)
{
	figure_pipes_com(cmd_splitted, cmd_index, cmd_struct);
	figure_in_out_files(&cmd_splitted[cmd_index], cmd_struct);
	identify_cmds(&cmd_splitted[cmd_index]);
	identify_cmd_opt(&cmd_splitted[cmd_index]);
	identify_args(&cmd_splitted[cmd_index]);
}