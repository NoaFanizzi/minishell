/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:13:15 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/30 09:54:04 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"



size_t	find_last_red_out()
{
	
}
//only valid input to read from is the rightmost one,
//only place where the output is going is the rightmost one
//altough there is nothing going in inbetween files when outputing, they are created
//that is not the case for inputs, if they dont exist they are not created
//also output files are created although the command doesnt work
void	figure_int_out_files(char **cmd, t_content **content, size_t cmd_index)
{
	
}

void	create_cmd_struct(char ***cmd_splitted, t_content **content, size_t cmd_index)
{
	figure_in_out_files(&cmd_splitted[cmd_index], content, cmd_index);
	identify_cmds(&cmd_splitted[cmd_index]);
	identify_cmd_opt(&cmd_splitted[cmd_index]);
	identify_args(&cmd_splitted[cmd_index]);
}