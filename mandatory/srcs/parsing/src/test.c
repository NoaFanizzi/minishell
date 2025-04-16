/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:08:46 by nbodin            #+#    #+#             */
/*   Updated: 2025/04/16 15:40:36 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	ft_check_if_command(char *cmd, char **path)
{
	if (access(cmd, X_OK) == 0)
	{
		*path = ft_strdup(cmd);
		return (0);
	}
	return (1);
}

int ft_is_command(t_expar *expar, char *command)
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

int	ft_try(char **env, char *command)
{
	t_expar expar;
	t_list *var;

	var = ft_init_env(env); //init la copie de la variable d'envrionnement
	expar.options = ct_get_paths(var); // separe path avec les differents chemins
	if(ft_is_command(&expar, command) == 0) // essaye d'access avec tous les chemins possibles. Si ça return 0 ça veut dire que c'est une commande, et si ça return 1 ça veut dire que c'est pas uen commande
		return(0);
	return(1);
}

char	**ct_get_paths(t_list *var)
{
	//size_t	size;
	char	**options;
	t_env	*cpy;

	cpy = (t_env *)var->content;
	while (var && ft_strncmp(cpy->var, "PATH", 4) != 0)
	{
		var = var->next;
		cpy = (t_env *)var->content;
	}
	//size = ft_strlen(cpy->var);
	options = ft_split(cpy->arg, ':');
	//ft_display_tab(options);
	return (options);
}

t_list	*ft_init_env(char **o_env)
{
	size_t	i;
	t_list *env;
	t_env	*new_env;

	env = NULL;
	i = 0;
	while(o_env[i])
	{
		new_env = ft_add_new_link(o_env[i]);
		ft_lstadd_back(&env, ft_lstnew(new_env));
		i++;
	}
	//env->next = NULL;
	return(env);
}

t_env	*ft_add_new_link(char *env)
{
	size_t	i;
	size_t	length;
	t_env *link;

	i = 0;
	link = ft_calloc(1, sizeof(t_env));
	(link)->exp = 0;
	while((env[i] != '+' && env[i] != '=')
		&&(env[i] != '\0'))
		i++;
	length = i;
	if(env[i] == '+')
	{
		(link)->op = ft_strdup("+=");
		i += 2;
	}
	if(env[i] == '=')
	{
		(link)->op = ft_strdup("=");
		i++;
	}
	if(env[i] == '\0')
		(link)->arg = NULL;
	if(env[i] != '\0')
		(link)->arg = ft_strdup(&env[i]);
	(link)->var = ft_calloc((length + 1), sizeof(char));
	i = 0;
	while(i < length)
	{
		(link)->var[i] = env[i];
		i++;
	}
	(link)->var[i] = '\0';
	return(link);
}