/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:22:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/16 13:33:03 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_pwd(t_list **env)
{
	//t_list *current;
	t_env *current;
	t_env *link;
	char	*path;

	link = NULL;
	path = NULL;
	path = getcwd(NULL, 0);
	current = get_env("PWD", *env);
	if(!current)
		return(1);
	free(current->arg);
	current->arg = ft_strdup(path);
	free(path);
	return(0);
}

int	ft_access_dir(t_content *content)
{
	if (chdir(content->arg[0]) == -1)
	{
		content->error_code = 1;
		ft_putstr_fd("maxishell: cd: ", STDERR_FILENO);
		perror(content->arg[0]);
		return(1);
	}
	return(0);
}

int	ft_update_opwd(t_list **env)
{
	//t_list *current;
	t_env	*current_path;
	t_env	*old_path;
	
	old_path = NULL;
	current_path = NULL;
	current_path = get_env("PWD", *env);
	old_path = get_env("OLDPWD", *env);
	free(old_path->arg);
	old_path->arg = ft_strdup(current_path->arg);
	if(!old_path->arg)
	{
		printf("aberrant\n");
		return(1);
	}
	return(0);
}

int	ft_find_wave(t_list *env, t_content *content)
{
	t_env *cpy;

	while(env)
	{
		cpy = (t_env *)env->content;
		if(ft_strncmp(cpy->var, "HOME", 4) == 0 && ft_strlen(cpy->var) == 4)
		{
			if(cpy->arg == NULL)
				return(0);
			content->arg = ft_calloc(ft_strlen(cpy->arg) + 1, sizeof(char *));
			content->arg[0] = ft_strdup(cpy->arg);
			content->arg[1] = NULL;
			content->error_code = 0;
			return(1);
		}
		env = env->next;
	}
	cpy = get_env("HOME", env);
	content->arg = ft_calloc(ft_strlen(cpy->arg) + 1, sizeof(char *));
	if(!content->arg)
		return(0);
	content->arg[0] = ft_strdup(cpy->arg);
	if(!content->arg[0])
		return(0);
	content->arg[1] = NULL;
	content->error_code = 0;
	return(1);
}

int	ft_find_dash(t_list *env, t_content *content)
{
	t_env *cpy;

	cpy = get_env("OLDPWD", env);
	if(cpy->arg == NULL)
		return(0);
	content->arg = ft_calloc(ft_strlen(cpy->arg) + 1, sizeof(char *));
	content->arg[0] = ft_strdup(cpy->arg);
	if(content->arg[0] == NULL)
		return(0);
	content->error_code = 0;
	return(1);
}

int	ft_deal_with_dash(t_content *content, t_list **env, int *params)
{
	if(ft_tablen(content->cmd) > 1 && ft_strcmp(content->cmd[1], "-") == 0)
	{
		*params = 1;
		if(ft_find_dash(*env, content) == 1)
			return (1);
		ft_putstr_fd("maxishell: cd: OLDPWD not set\n", STDERR_FILENO);
		content->error_code = 1;
		return(2);
	}
	return(0);
}

int	ft_deal_with_wave(t_content *content, t_list **env, int *params)
{
	if(ft_find_wave(*env, content) == 1)
		return (1);
	ft_putstr_fd("maxishell: cd: HOME not set\n", STDERR_FILENO);
	content->error_code = 1;
	*params = 1;
	return(2);
}

void	ft_cd(t_content *content, t_list **env)
{
	int params;

	params = 0;
	if(ft_tablen(content->arg) > 1)
	{
		content->error_code = 1;
		ft_putstr_fd("maxishell: cd: too many arguments\n", STDERR_FILENO);
		return;
	}
	if(ft_deal_with_dash(content, env, &params) == 2)
		return;
	if(!content->arg)
	{
		if(ft_deal_with_wave(content, env, &params) == 2)
			return;	
	}
	if(ft_access_dir(content) == 1)
		return;
	if(ft_update_opwd(env) == 1)
		return;
	if(ft_update_pwd(env) == 1)
		return;
	if(params == 1)
		ft_putendl_fd(content->arg[0], STDOUT_FILENO);
	content->error_code = 0;

}

