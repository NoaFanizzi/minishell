/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:54:42 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/08 12:30:50 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_command(char *cmd, char *path)
{
	if (access(cmd, X_OK) == 0)
	{
		path = ft_strdup(cmd);
		return (0);
	}
	return (1);
}

int ft_is_command(t_expar *expar, t_content *content,  t_var *var)
{
	size_t	i;
	char	*adding_slash;

	i = 0;
	(void)var;
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
	if(ft_check_if_command(content->cmd[0], expar->path) == 0)
		return (0);
	return (1);
}

void	ft_is_built_in(t_expar *expar, t_content *content, t_var *var)
{
	(void)var;
	if(ft_strncmp(content->cmd[0], "echo", 4) == 0 && ft_strlen(content->cmd[0]) == 4)
		ft_echo(content, expar);
	return;
}

static int	ft_prepare_execution(t_expar *expar, t_content *content, t_var *var)
{
	// if(content->input == -2) // c'est un pipe
	// {
	// 	expar->fd = -2;
	// 	return(1);
	// }
	// expar->fd = open(content->input, O_RDONLY);
	// if (expar->fd == -1)
	// {
	// 	perror("Infile");
	// 	close(expar->pipe[0]);
	// 	close(expar->pipe[1]);
	// 	free_tab(expar->options);
	// 	exit(1);
	// }
	if(content->arg)
	{
		if(content->cmd[1] == NULL)
		{
			content->cmd[1] = ft_strdup(content->arg);
			free(content->arg);
		}
		else
		{
			content->cmd[2] = ft_strdup(content->arg);
			free(content->arg);
		}
	}
	ft_is_built_in(expar, content, var);
	if (ft_is_command(expar, content, var) == 1)
	{
		//ft_try_builtin et si c'est pas bon, la faut faut print command not found et faire tout le reste
		ft_putstr_fd("Command not found\n", 1);
		ft_free_tab(content->cmd);
		ft_free_tab(expar->options);
		ft_close_all(expar, content);
		exit(127);
	}
	return(0);
}

void	ft_get_right_release(t_content *content, t_expar *expar)
{
	if(content->input != -2)
	{
		if (dup2(content->input, STDIN_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
	if(content->input == -2)
	{
		if (dup2(expar->pipe[0], STDIN_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
	if(content->output != -2)
	{
		if (dup2(content->output, STDOUT_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
	if(content->output == -2) //ici probleme
	{
		if (dup2(expar->pipe[1], STDOUT_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
}

void	ft_exec_cmd(t_expar *expar, t_content *content, t_var *var)
{
	printf("content->input = %d\n", content->input);
	printf("content->output = %d\n", content->output);
	printf("content->cmd[0] = %s\n", content->cmd[0]);
	//printf("content->arg = %s\n\n", content->arg);
	printf("expar->pipe[0] = %d\n", expar->pipe[0]);
	printf("expar->pipe[1] = %d\n", expar->pipe[1]);
	printf("--------------------\n");
	ft_get_right_release(content, expar);
	ft_prepare_execution(expar, content, var);
	ft_close_all(expar, content);
	ft_free_tab(expar->options);
	if (execve(expar->path, content->cmd, var->env) == -1)
	{
		perror("execve");
		free(expar->path);
		ft_free_tab(content->cmd);
		exit(EXIT_FAILURE);
	}
}

//TODO: Bien reorganiser les fonctions de free correctement, c'est degeulasse, je pense que rien n'est free au bon endroit a cause du changement dans l'ancienne strcture et de l'integration de la nouvelle