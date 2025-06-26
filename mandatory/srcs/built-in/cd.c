/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:22:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/26 16:51:29 by nofanizz         ###   ########.fr       */
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

int	ft_find_wave(t_list *env, t_content *content)
{
	t_env *cpy;

	while(env)
	{
		cpy = (t_env *)env->content;
		if(ft_strncmp(cpy->var, "HOME", 4) == 0 && ft_strlen(cpy->var) == 4)
		{
			content->arg = ft_calloc(ft_strlen(cpy->arg) + 1, sizeof(char *));
			content->arg[0] = ft_strdup(ft_strdup(cpy->arg));
			content->arg[1] = NULL;
			return(1);
		}
		env = env->next;
	}
	return(0);
}

int	ft_find_dash(t_list *env, t_content *content)
{
	t_env *cpy;

	while(env)
	{
		cpy = (t_env *)env->content;
		if(ft_strncmp(cpy->var, "OLDPWD", 6) == 0 && ft_strlen(cpy->var) == 6)
		{
			content->arg = ft_calloc(ft_strlen(cpy->arg) + 1, sizeof(char *));
			content->arg[0] = ft_strdup(ft_strdup(cpy->arg));
			content->arg[1] = NULL;
			ft_putstr_fd(content->arg[0], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			return(1);
		}
		env = env->next;
	}
	return(0);
}

int	ft_deal_with_dash(t_content *content, t_list **env)
{
	if((ft_tablen(content->cmd) > 1 && ft_strncmp(content->cmd[1], "-", 1) == 0)
		&&(ft_strlen(content->cmd[1]) == 1))
	{
		if(ft_find_dash(*env, content) == 1)
			return (1);
		ft_putstr_fd("bash: cd: OLDPWD not set\n", STDERR_FILENO);
		return(2);
	}
	return(0);
}

int	ft_deal_with_wave(t_content *content, t_list **env)
{
	if(ft_find_wave(*env, content) == 1)
		return (1);
	//printf("pas trouve\n");
	ft_putstr_fd("bash: cd: HOME not set\n", STDERR_FILENO);
	return(2);
}

void	ft_cd(t_content *content, t_list **env)
{
	if(ft_tablen(content->arg) > 1)
	{
		ft_putstr_fd("maxishell: cd: too many arguments\n", STDERR_FILENO);
		return;
	}
	if(ft_deal_with_dash(content, env) == 2)
		return;
	if(!content->arg)
	{
		if(ft_deal_with_wave(content, env) == 2)
		return;	
	}
	ft_update_opwd(env);
	if (chdir(content->arg[0]) == -1)
	{
		ft_putstr_fd("maxishell: cd: ", STDERR_FILENO);
		perror(content->arg[0]);
	}
	ft_update_pwd(env);
}

