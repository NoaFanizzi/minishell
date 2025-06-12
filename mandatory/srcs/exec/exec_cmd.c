/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:54:42 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/12 13:05:07 by nofanizz         ###   ########.fr       */
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

	i = 0;
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
	if(ft_check_if_command(content->cmd[0], &expar->path) == 0)
		return (0);
	return (1);
}

void	ft_is_built_in_child(t_expar *expar, t_content *content, t_list **env)
{
	int return_value;
	
	return_value = 0;
	if(ft_strncmp(content->cmd[0], "echo", 4) == 0 && ft_strlen(content->cmd[0]) == 4)
		return_value = ft_echo(content);
	else if(ft_strncmp(content->cmd[0], "export", 6) == 0 && ft_strlen(content->cmd[0]) == 6)
		return_value = ft_export(env, content);
	else if(ft_strncmp(content->cmd[0], "unset", 5) == 0 && ft_strlen(content->cmd[0]) == 5)
		return_value = ft_unset(env, content);
	else
		return;
	ft_free_env(*env);
	//ft_free_array_content(array);
	ft_free_tab(expar->options);
	ft_free_content(content);
	close(expar->pipe[0]);
	close(expar->pipe[1]);
	exit(return_value);
}

static int	ft_prepare_execution(t_expar *expar, t_content *content, t_list **env)
{
	ft_is_built_in_child(expar, content, env);
	if (ft_is_command(expar, content) == 1)
	{
		//ft_try_builtin et si c'est pas bon, la faut faut print command not found et faire tout le reste
		free(expar->path);
		ft_putstr_fd("Command not found\n", 1);
		ft_free_tab(content->cmd);
		ft_free_tab(expar->options);
		ft_close_all(expar, content);
		exit(127);
	}
	return(0);
}

void	ft_get_right_release(t_content *content, t_expar *expar, int type, int channel)
{
	if(type == IN && channel == 0)
	{
		if (dup2(content->infile, STDIN_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
	if(type == PIPE && channel == 0)
	{
		if (dup2(expar->pipe[0], STDIN_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}

	if(type == OUT && channel == 1)
	{
		if (dup2(content->outfile, STDOUT_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
	if(type == PIPE && channel == 1) //ici probleme
	{
		if (dup2(expar->pipe[1], STDOUT_FILENO) == -1)
			ft_dup2_pb (expar, content);
	}
}
//Cette fonction permet de savoir si y'a un pipe a la fin et/ou plusieurs outfile ce aui permet d'ouvrir et de creer chaque fichier correctement
int	ft_get_outfile(t_content *content)
{
	size_t	i;
	int	type;

	i = 0;
	type = -1;
	content->outfile = -2;
	if(content->size > 1 && content->pos != content->size)
		return(PIPE);
	if(content->files == NULL)
		return(STDOUT);
	while(&content->files[i])
	{
		if(content->files[i].type == OUT)
		{
			if(content->outfile != -2)
				close(content->outfile);
			content->outfile = open(content->cmd_splitted[content->pos][content->files[i].index], O_RDWR | O_CREAT | O_TRUNC, 0644);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
			if(content->outfile == -1)
				return(1); //fait les trucs
			type = IN;
		}
		i++;
	}
	if(type != -1)
		return(type);
	return(type);
}

int	ft_get_infile(t_content *content)
{
	size_t	i;
	int	type;

	i = 0;
	type = -1;
	content->infile = -2;
	if(content->size > 1 && content->pos > 0)
		return(PIPE);
	if(content->files == NULL)
		return(STDIN);
	while(&content->files[i])
	{
		if(content->files[i].type == IN)
		{
			if(content->infile != -2)
				close(content->infile);
			content->infile = open(content->cmd_splitted[content->pos][content->files[i].index], O_RDWR);//TODO ducoup l'index c'est le fichier ou le token > ou < ?
			if(content->infile == -1)
				return(1); //fait les trucs
			type = IN;
		}
		i++;
	}
	if(type != -1)
		return(type);
	return(type);
}

void	ft_parse_redirections(t_content *content, t_expar *expar)
{
	int type;

	type = ft_get_infile(content);
	if(type == IN)
		ft_get_right_release(content, expar, IN, 0);
	if(type == PIPE)
		ft_get_right_release(content, expar, PIPE, 0);
	type = ft_get_outfile(content);
	//printf("test1\n");
	//printf("TYPE = %d\n", type);
	//printf("content->size = %d\n", content->size);
	if(type == OUT)
		ft_get_right_release(content, expar, OUT, 1);
	if(type == PIPE)
		ft_get_right_release(content, expar, PIPE, 1);
}

size_t	ft_tablen(char **tab)
{
	size_t	i;

	i = 0;
	while(tab[i])
	{
		i++;
	}
	return(i);
}

char **ft_cmd_join(char **a, char **b)
{
	size_t	i;
	size_t	j;
	size_t	length;
	char **cmd;

	i = 0;
	j = 0;
	length = ft_tablen(a) + ft_tablen(b);
	cmd = ft_calloc(length + 1, (sizeof (char *)));
	while(i < ft_tablen(a))
	{
		cmd[i] = ft_strdup(a[i]);
		i++;
	}
	while(j < ft_tablen(b))
	{
		cmd[i] = ft_strdup(b[j]);
		i++;
		j++;
	}
	cmd[i] = NULL;
	ft_display_tab(cmd);
	ft_free_tab(a);
	ft_free_tab(b);
	return(cmd);
	
}

void	ft_exec_cmd(t_expar *expar, t_content *content, t_list **env)
{
	char **env_converted;

	env_converted = NULL;

	//ft_display_tab(content->cmd);
	ft_parse_redirections(content, expar);
	ft_prepare_execution(expar, content, env);
	ft_close_all(expar, content);
	ft_free_tab(expar->options);
	env_converted = ft_convert_env(*env);
	content->cmd = ft_cmd_join(content->cmd, content->arg);
	if (execve(expar->path, content->cmd, env_converted) == -1)
	{
		perror("execve");
		free(expar->path);
		ft_free_tab(content->cmd);
		exit(EXIT_FAILURE);
	}
}

//TODO: Bien reorganiser les fonctions de free correctement, c'est degeulasse, je pense que rien n'est free au bon endroit a cause du changement dans l'ancienne strcture et de l'integration de la nouvelle