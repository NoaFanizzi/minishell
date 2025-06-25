/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:22:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/25 12:51:53 by nofanizz         ###   ########.fr       */
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
	if(!content->arg)
	{
		ft_putstr_fd("maxishell: cd: Invalid arguments\n", STDERR_FILENO);
		return;
	}
	if(ft_update_opwd(env) == 1)
	{
		// ft_putstr_fd(content->arg[0], STDERR_FILENO);
		// ft_putstr_fd(": No such file or directory", STDERR_FILENO);
	}
	if (chdir(content->arg[0]) == -1)
	{
		ft_putstr_fd("maxishell: cd: ", STDERR_FILENO);
		perror(content->arg[0]);
		//ft_putstr_fd("\n", STDERR_FILENO);
		
	}
	ft_update_pwd(env);
}

