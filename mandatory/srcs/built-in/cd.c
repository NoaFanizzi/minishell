/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:22:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/30 08:22:45 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_pwd(t_list **env)
{
	t_list *current;
	t_env *link;
	char	*path;

	path = getcwd(NULL, 0);
	//printf("path after change = %s\n", path);
	link = NULL;
	current = *env;
	while(current)
	{
		link = (t_env *)current->content;
		if(ft_strncmp(link->var, "PWD", 3) == 0 && ft_strlen(link->var) == 3)
		{
			free(link->arg);
			link->arg = ft_strdup(path);
			free(path);
			return(0);
		}
		current = current->next;
	}
	free(path);
	return(1);
}

int	ft_update_opwd(t_list **env)
{
	t_list *current;
	t_env *link;
	char	*path;
	
	link = NULL;
	path = getcwd(NULL, 0);
	current = *env;
	while(current)
	{
		link = (t_env *)current->content;
		if(ft_strncmp(link->var, "OLDPWD", 6) == 0 && ft_strlen(link->var) == 6)
		{
			free(link->arg);
			link->arg = ft_strdup(path);
			free(path);
			return(0);
		}
		current = current->next;
	}
	free(path);
	return(1);
}

void	ft_cd(t_content *content, t_list **env)
{
	ft_update_opwd(env);
	if (chdir(content->arg) == -1)
		write(1, "chdir error", 12);
	ft_update_pwd(env);
}

