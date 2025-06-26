/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:34:46 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/26 09:23:01 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_built_in_dad(t_array *array, t_list **env)
{
	if(ft_strncmp(array->content->cmd[0], "export", 6) == 0 && ft_strlen(array->content->cmd[0]) == 6)
		ft_export(env, &array->content[0]);
	if(ft_strncmp(array->content->cmd[0], "unset", 5) == 0 && ft_strlen(array->content->cmd[0]) == 5)
		ft_unset(env, &array->content[0]);
	if(ft_strncmp(array->content->cmd[0], "pwd", 3) == 0 && ft_strlen(array->content->cmd[0]) == 3)
		ft_pwd();
	if(ft_strncmp(array->content->cmd[0], "cd", 2) == 0 && ft_strlen(array->content->cmd[0]) == 2)
		ft_cd(&array->content[0], env);
	if(ft_strncmp(array->content->cmd[0], "echo", 4) == 0 && ft_strlen(array->content->cmd[0]) == 4)
		ft_echo(&array->content[0]);
	if(ft_strncmp(array->content->cmd[0], "exit", 4) == 0 && ft_strlen(array->content->cmd[0]) == 4)
	{
		ft_free_content(&array->content[0]);
		ft_free_env(*env);
		exit(0);
	}
	if(ft_strncmp(array->content->cmd[0], "env", 3) == 0 && ft_strlen(array->content->cmd[0]) == 3)
		ft_display_env(*env);
}

int	ft_get_redir_dad(t_array *array, t_list **env)
{
	int	stdin_saved;
	int	stdout_saved;
	int command;
	
	stdin_saved = dup(STDIN_FILENO);
	stdout_saved = dup(STDOUT_FILENO);
	ft_parse_redirections(&array->content[0]);
	command = ft_is_built_in(&array->content[0]);
	if(command == 0)
	{
		ft_is_built_in_dad(array, env);
	}
	if(command == 1)
	{
		dup2(stdin_saved, STDIN_FILENO);
		close(stdin_saved);
		dup2(stdout_saved, STDOUT_FILENO);
		close(stdout_saved);
		return(1);
	}
	dup2(stdin_saved, STDIN_FILENO);
	close(stdin_saved);
	dup2(stdout_saved, STDOUT_FILENO);
	close(stdout_saved);
	return(0);
}



int	ft_is_built_in(t_content *content)
{
	if (!content->cmd || !content->cmd[0])
		return (2);
	if((ft_strncmp(content->cmd[0], "export", 6) == 0 && ft_strlen(content->cmd[0]) == 6)
		||(ft_strncmp(content->cmd[0], "unset", 5) == 0 && ft_strlen(content->cmd[0]) == 5)
		||(ft_strncmp(content->cmd[0], "pwd", 3) == 0 && ft_strlen(content->cmd[0]) == 3)
		||(ft_strncmp(content->cmd[0], "cd", 2) == 0 && ft_strlen(content->cmd[0]) == 2)
		||(ft_strncmp(content->cmd[0], "exit", 4) == 0 && ft_strlen(content->cmd[0]) == 4)
		||(ft_strncmp(content->cmd[0], "echo", 4) == 0 && ft_strlen(content->cmd[0]) == 4)
		||(ft_strncmp(content->cmd[0], "env", 3) == 0 && ft_strlen(content->cmd[0]) == 3))
		//||(ft_strncmp(content->cmd[0], "echo", 4) == 0 && ft_strlen(content->cmd[0]) == 4))
		return(0);
	return(1);
}

// void	ft_printf_error_message(t_content *content)
// {
// 	if(g_exit_status == )
// }

void	ft_wait_pid(t_array *array)
{
	pid_t pid;
	//int	i;
	int status;

	//i = 0;
	status = 0;
	(void)array;
	pid = waitpid(-1, &status, 0);
	while(pid > 0)
	{
		//printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		if(WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if(WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		//ft_print_error_message(array->content[i]);
		pid = waitpid(-1, &status, 0);
	}
}

void	ft_display_array_content(t_array *array)
{
	int	i;

	i = 0;
	while(i < array->size)
	{
		printf("content[%d] : \n\n", i);
		printf("-----cmd-----|\n");
		ft_display_tab(array->content[i].cmd);
		printf("-------------|\n\n");
		printf("-----args----|\n");
		ft_display_tab(array->content[i].arg);
		printf("-------------|\n\n");
		//printf("infile : %d\n", array->content[i].infile);
		//printf("outfile : %d\n", array->content[i].outfile);
		i++;
	}
}

void	ft_init_pipe(t_array *array)
{
	int	i;

	i = 0;

	array->pipe = malloc(sizeof(*array->pipe) * (array->size - 1));
	while(i < array->size - 1)
	{
		if (pipe(array->pipe[i]) == -1)
		{
			perror("pipe");
			ft_exit(&array->content[0]);
		}
		i++;
	}
}

void	ft_close_pipes(t_array *array)
{
	int	i;

	i = 0;
	// if(expar->size == 1)
	// {
	// 	if(expar->pipe)
	// 	{
	// 		close(expar->pipe[i][0]);
	// 		close(expar->pipe[i][1]);
	// 	}
	// 	i++;
	// }
	while(i < array->size - 1)
	{
		if(array->pipe)
		{
			close(array->pipe[i][0]);
			close(array->pipe[i][1]);
		}
		i++;
	}
	free(array->pipe);
	array->pipe = NULL;
}

void	ft_init_exec(t_list **env, t_array *array)
{
	int	i;
	int redir_value;

	i = 0;
	redir_value = 0;
	array->content[0].size = array->size; // important ne pas supprimer cette lign esinon ça pète dans redir_dad
	
	//ft_display_array_content(array);

	while(i < array->size)
	{
		array->content[i].array_ptr = array;
		array->content[i].expar = NULL;

		i++;
	}
	i = 0;
	if(array->size == 1)
	{
		redir_value = ft_get_redir_dad(array, env);
		if(redir_value == 0 || redir_value == 2)
			return;
	}
	

	ft_init_pipe(array);

	while(i < array->size)
	{
		array->content[i].env = env;
		array->content[i].pos = i;
		array->content[i].size = array->size;
		array->content[i].pid = fork();
		if (array->content[i].pid == -1)
			ft_exit(&array->content[i]);
		if (array->content[i].pid == 0)
		{
			//ft_free_others(array, i);
			ft_exec_cmd(&array->content[i], env);
		}
		i++;
	}
	//printf("array.size = %d\n", array->size);
	ft_close_pipes(array);
	ft_wait_pid(array);
 	//ft_free_tab(expar.options);
}

