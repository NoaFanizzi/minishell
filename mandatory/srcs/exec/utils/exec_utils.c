/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:17:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/07 16:25:43 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (tab == NULL || tab[0] == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

char	**ct_get_paths(t_list *var, t_content *content)
{
	char	**options;
	t_env	*cpy;

	options = NULL;
	if (!var)
		return (NULL);
	cpy = get_env("PATH", var);
	if (cpy == NULL)
		return (NULL);
	options = ft_split(cpy->arg, ':'); //PROTECTED
	if (!options)
	{
		ft_open_error(content, NULL);
		content->expar->options = NULL;
		ft_exit(content);
	}
	if (!options[0])
	{
		free(options);
		options = NULL;
	}
	return (options);
}

char	**ft_cmd_join(char **a, char **b, t_content *content)
{
	size_t	length;
	char	**cmd;

	length = ft_tablen(a) + ft_tablen(b);
	cmd = ft_calloc(length + 1, (sizeof(char *))); //PROTECTED
	if (!cmd)
	{
		if (content->cmd)
			ft_free_tab(content->cmd);
		content->cmd = NULL;
		return (NULL);
	}
	if (load_cmd_tab(&a, &b, content, &cmd) == 0)
		return (NULL);
	if (a)
		ft_free_tab(a);
	if (b)
		ft_free_tab(b);
	return (cmd);
}

int	ft_contains_dir(char *path)
{
	if ((path[0] == '/') || (ft_strncmp(path, "./", 2) == 0)
		|| (ft_strncmp(path, "../", 3) == 0) || (ft_strcmp(path, "..") == 0)
		|| (ft_strcmp(path, ".") == 0))
		return (1);
	return (0);
}

void	ft_display_env(t_list *env, t_content *content)
{
	t_env	*cpy;

	if (!env)
	{
		content->error_code = 1;
		ft_putstr_fd("maxishell: env: env variable not set\n", STDERR_FILENO);
		return ;
	}
	while (env)
	{
		cpy = (t_env *)env->content;
		if (cpy->op)
		{
			ft_putstr_fd(cpy->var, 1);
			ft_putstr_fd(cpy->op, 1);
			ft_putstr_fd(cpy->arg, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	content->error_code = 0;
}
