/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:11:11 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/14 15:16:33 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_command(char *cmd, char **path)
{
	if (access(cmd, X_OK) == 0)
	{
		*path = ft_strdup(cmd);
		return (0);
	}
	return (1);
}

int ft_is_command(t_expar *expar, t_content *content)
{
	size_t	i;
	char	*adding_slash;

	i = 0;
	if (content->cmd == NULL)
		return (1);
	while (expar->options[i])
	{
		adding_slash = ft_strjoin(expar->options[i], "/");
		if (!adding_slash)
			return (1);
		expar->path = ft_strjoin(adding_slash, content->cmd[0]);
		//printf("path = %s\n", expar->path);
		free(adding_slash);
		if (!expar->path)
			return (1);
		if (access(expar->path, X_OK) == 0)
			return (0);
		free(expar->path);
		i++;
	}
	if(ft_check_if_command(content->cmd[0], &expar->path) == 0)
		return (0);
	return (1);
}

void	ft_try(char **env)
{
	t_expar expar;
	t_list *var;
	t_content *content;

	var = ft_init_env(env); //init la copie de la variable d'envrionnement
	expar.options = ct_get_paths(env); // separe path avec les differents chemins
	ft_is_command(&expar, content);
}