/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:23:30 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/03 13:13:30 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_content *content)
{
	char *path;

	path = getcwd(NULL, 0);
	if(!path)
	{
		content->error_code = 1;
		perror("pwd error");
		return (1);
	}
	content->error_code = 0;
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
}
