/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:54:42 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/19 18:07:23 by nofanizz         ###   ########.fr       */
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

	expar->path = NULL;
	i = 0;
	if (content->cmd == NULL || !content->cmd[0])
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

void	ft_is_built_in_child(t_expar *expar, t_content *content, t_list **env, t_array *array)
{
	int return_value;
	
	return_value = 0;
	if (!content->cmd[0])
		return;
	if(ft_strncmp(content->cmd[0], "echo", 4) == 0 && ft_strlen(content->cmd[0]) == 4)
		return_value = ft_echo(content);
	else if(ft_strncmp(content->cmd[0], "export", 6) == 0 && ft_strlen(content->cmd[0]) == 6)
		return_value = ft_export(env, content);
	else if(ft_strncmp(content->cmd[0], "unset", 5) == 0 && ft_strlen(content->cmd[0]) == 5)
		return_value = ft_unset(env, content);
	else
		return;
	ft_free_env(*env);
	ft_free_tab(expar->options);
	free_command(content->cmd_splitted);
	ft_free_array_content(array);
	close(expar->pipe[0]);
	close(expar->pipe[1]);
	exit(return_value);
}

static int	ft_prepare_execution(t_expar *expar, t_content *content, t_list **env, t_array *array)
{
	ft_is_built_in_child(expar, content, env, array);
	if (ft_is_command(expar, content) == 1)
	{
		//ft_try_builtin et si c'est pas bon, la faut faut print command not found et faire tout le reste
		ft_putstr_fd(content->cmd[0], STDERR_FILENO);
		ft_putstr_fd(" command not found\n", STDERR_FILENO);
		free(expar->path);
		ft_free_tab(expar->options);
		ft_free_env(*env);
		ft_close_all(expar, content);
		ft_free_content(content);
		exit(127);
	}
	return(0);
}

int	ft_is_redir(char **tab)
{
	size_t	i;

	i = 0;
	while(tab[i])
	{
		if(ft_strncmp(tab[i], ">", 1) == 0 && ft_strlen(tab[i]) == 1)
			return(1);
		i++;
	}
	return(0);
}

char **ft_get_args(t_content *content)
{
	size_t	i;
	size_t	j;
	size_t	length;
	char **new_tab;

	i = 0;
	j = 0;
	while(content->arg[i])
	{
		if(ft_strncmp(content->arg[i], ">", 1) == 0 && ft_strlen(content->arg[i]) == 1)
		{
			break;
		}
		i++;
	}
	//printf("contentttttttt->arg[i] = %s et i = %zu\n", content->arg[i], i);
	if(content->arg[i])
	{
		//printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		length = i;
		i = 1;
		new_tab = ft_calloc((ft_tablen(&content->arg[i]) + 1), sizeof(char *));
		while(content->arg[i] && i < length - 1)
		{
			new_tab[j] = ft_strdup(content->arg[i]);
			j++;
			i++;
		}
	}
	else
	{
		//printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n");
		i = 0;
		new_tab = ft_calloc((ft_tablen(&content->arg[i]) + 1), sizeof(char *));
		while(content->arg[i])
		{
			new_tab[j] = ft_strdup(content->arg[i]);
			j++;
			i++;
		}
	}
	ft_free_tab(content->arg);
	return(new_tab);
}


void	ft_exec_cmd(t_expar *expar, t_content *content, t_list **env, t_array *array)
{
	char **env_converted;
	env_converted = NULL;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	size_t	i = 0;
	// printf("BEFOREEEEE\n\n");
	// i = 0;
	// while(content->arg[i])
	// {
	// 	printf("content->arg[%d] = %s\n", i, content->arg[i]);
	// 	i++;
	// }
	// printf("---------------\n");
	// //content->arg = ft_get_args(content);
	// i = 0;
	// while(content->arg[i])
	// {
	// 	printf("content->arg[%d] = %s\n", i, content->arg[i]);
	// 	i++;
	// }
	i = 0;		
	//int size = content->files[i].size;

	while(i < content->files->size)
	{
		printf("content->files[i].index = %d\n", content->files[i].index);
		printf("content->files[i].size = %zu\n", content->files[i].size);
		printf("content->files[i].type = %d\n\n", content->files[i].type);
		i++;
	}
	if(ft_parse_redirections(content, expar) == O_ERROR)
		ft_free_after_error(expar, content, env, array);
	ft_prepare_execution(expar, content, env, array);
	ft_close_all(expar, content);
	ft_free_tab(expar->options);
	env_converted = ft_convert_env(*env);
	content->cmd = ft_cmd_join(content->cmd, content->arg);
	//ft_display_tab(env_converted);
	//ft_display_tab(content->cmd);
	if (execve(expar->path, content->cmd, env_converted) == -1)
	{
		perror("execve");
		free(expar->path);
		ft_free_env(*env);
		ft_free_tab(content->cmd);
		exit(EXIT_FAILURE);
	}

}

//TODO: Bien reorganiser les fonctions de free correctement, c'est degeulasse, je pense que rien n'est free au bon endroit a cause du changement dans l'ancienne strcture et de l'integration de la nouvelle