/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:09:58 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/01 16:31:27 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <fcntl.h>
#include "get_next_line/get_next_line.h"

typedef struct s_content
{
	char **cmd;// Peut-etre faire un tableau de tableau pour cmd + options parce que moi je dois donner un tableau de tableau a execve
	char *arg;
	int input; // int ou char ? Est ce que j'open dans l'exec ou on open dans le parsing ?
	int output; //pareil pour l'output
	int overwrite;
	pid_t pid;


}			t_content;

typedef struct s_array
{
	t_content *content;
	int size;
}				t_array;

#endif