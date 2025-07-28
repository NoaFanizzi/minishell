/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:17:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/28 21:55:50 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	options = ft_split(cpy->arg, ':');
	if (!options)
		ft_exit(content);
	if (!options[0])
	{
		free(options);
		options = NULL;
	}
	return (options);
}

void	ft_free_tab_length(char **tab, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}


int	load_cmd_a(char ***a, t_content *content, char ***cmd, size_t	*i)
{
	size_t	len_a;

	len_a = ft_tablen(*a);

	*i = 0;
	while (*i < len_a)
	{
		(*cmd)[*i] = ft_strdup((*a)[*i]); // PROTECTED
		if (!(*cmd)[*i])
		{
			if (content->cmd)
				ft_free_tab(content->cmd);
			content->cmd = NULL;
			content->error_code = 1;
			ft_free_tab_length(*cmd, *i);
			return (0);
		}
		(*i)++;
	}
	return(1);
}

int	load_cmd_tab(char ***a, char ***b, t_content *content, char ***cmd)
{
	size_t	i;
	size_t	j;
	size_t	len_b;

	j = 0;
	len_b = ft_tablen(*b);
	if(load_cmd_a(a, content, cmd, &i) == 0)
		return(0);
	while (j < len_b)
	{
		(*cmd)[i + j] = ft_strdup((*b)[j]); //PROTECTED
		if (!(*cmd)[i + j])
		{
			if (content->cmd)
				ft_free_tab(content->cmd);
			content->cmd = NULL;
			ft_free_tab_length(*cmd, i + j);
			content->error_code = 1;
			return (0);
		}
		j++;
	}
	(*cmd)[i + j] = NULL;
	return (1);
}

char	**ft_cmd_join(char **a, char **b, t_content *content)
{
	size_t	length;
	char	**cmd;

	length = ft_tablen(a) + ft_tablen(b);
	cmd = ft_calloc(length + 1, (sizeof(char *))); // PROTECTED
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

void	ft_display_array_content(t_array *array)
{
	int	i;

	i = 0;
	while (i < array->size)
	{
		printf("content[%d] : \n\n", i);
		printf("-----cmd-----|\n");
		ft_display_tab(array->content[i].cmd);
		printf("-------------|\n\n");
		if (array->content[i].arg[0])
		{
			printf("-----args----|\n");
			ft_display_tab(array->content[i].arg);
			printf("-------------|\n\n");
		}
		i++;
	}
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
