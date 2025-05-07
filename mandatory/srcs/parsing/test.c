/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:08:46 by nbodin            #+#    #+#             */
/*   Updated: 2025/05/07 16:48:31 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_command_parsing(t_expar *expar, char *command)
{
	size_t	i;
	char	*adding_slash;

	i = 0;
	if (command == NULL)
		return (1);
	while (expar->options[i])
	{
		adding_slash = ft_strjoin(expar->options[i], "/");
		if (!adding_slash)
			return (1);
		expar->path = ft_strjoin(adding_slash, command);
		//printf("path = %s\n", expar->path);
		free(adding_slash);
		if (!expar->path)
			return (1);
		if (access(expar->path, X_OK) == 0)
			return (0);
		free(expar->path);
		i++;
	}
	if(ft_check_if_command(command, &expar->path) == 0)
		return (0);
	return (1);
}

int	ft_try(t_list *var, char *command)
{
	t_expar expar;

	expar.options = ct_get_paths(var); // separe path avec les differents chemins
	if(ft_is_command_parsing(&expar, command) == 0) // essaye d'access avec tous les chemins possibles. Si ça return 0 ça veut dire que c'est une commande, et si ça return 1 ça veut dire que c'est pas uen commande
	{
		free(expar.options);
		return(0);
	}
	free(expar.options);
	return(1);
}
