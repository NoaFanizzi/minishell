/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:54:42 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/28 14:06:22 by nofanizz         ###   ########.fr       */
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

int ft_is_command(t_expar *expar, t_content *content,  char **env)
{
	size_t	i;
	char	*adding_slash;

	i = 0;
	if (content->cmd == NULL)
		return (1);
	while (expar->options[i])
	{
		adding_slash = ft_strjoin(env[i], "/");
		if (!adding_slash)
			return (1);
		expar->path = ft_strjoin(adding_slash, content->cmd[0]);
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

static void	ft_prepare_execution(t_expar *expar, t_content *content, char **env)
{
	expar->fd = open(content->input, O_RDONLY);
	if (expar->fd == -1)
	{
		perror("Infile");
		close(expar->pipe[0]);
		close(expar->pipe[1]);
		free_tab(expar->options);
		exit(1);
	}
	if (ft_is_command(expar, content, env) == 1)
	{
		//ft_try_builtin et si c'est pas bon, la faut faut print command not found et faire tout le reste
		ft_putstr_fd("Command not found\n", 1);
		free_tab(content->cmd);
		free_tab(expar->options);
		ft_close_all(expar);
		exit(127);
	}
}

void	ft_first_cmd(t_expar *expar, t_content *content, char **env)
{
	ft_prepare_execution(expar, content, env);
	
	if(content->input != NULL)
	{
		if (dup2(content->input, STDIN_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
	if(content->output != NULL)
	{
		if(content->output == -1) // tu set un fd negatif comme ca je sais que y'a pas d'output dnas le cas ou tu m' envoies un int. Mais si tu m 'envoies un char *, dans ce cas la tu pourras me le set a nul. Et en vrai je pense que c'est mieux que tu me l'envoies en char *
		{
			if (dup2(expar->pipe[1], STDOUT_FILENO) == -1)
				ft_dup2_pb (expar, content);
			}
			else
			{
				if (dup2(content->output, STDOUT_FILENO) == -1)
					ft_dup2_pb (expar, content);
			}
	}
	ft_close_all(expar);
	free_tab(expar->options);
	if (execve(expar->path, content->cmd, env) == -1)
	{
		perror("execve");
		free(expar->path);
		free_tab(content->cmd);
		exit(EXIT_FAILURE);
	}
}

void	ft_second_cmd(t_expar *expar, t_content *content, char **env)
{
	ft_prepare_execution(expar, content, env);
	
	if(content->input != NULL)
	{
		if (dup2(content->input, STDIN_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
	if(content->output != NULL)
	{
		if (dup2(content->input, STDOUT_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
	ft_close_all(expar);
	free_tab(expar->options);
	if (execve(expar->path, content->cmd, env) == -1)
	{
		perror("execve");
		free(expar->path);
		free_tab(content->cmd);
		exit(EXIT_FAILURE);
	}
}

//TODO: Bien reorganiser les fonctions de free correctement, c'st degeulasse, je pense que rien n'est free au bon endroit a cause du changement dans l'ancienne strcture et de l'integration de la nouvelle