/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:34:46 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/19 18:03:33 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_built_in_dad(t_content *content, t_list **env)
{
	if(ft_strncmp(content->cmd[0], "export", 6) == 0 && ft_strlen(content->cmd[0]) == 6)
		ft_export(env, content);
	if(ft_strncmp(content->cmd[0], "unset", 5) == 0 && ft_strlen(content->cmd[0]) == 5)
		ft_unset(env, content);
	if(ft_strncmp(content->cmd[0], "pwd", 3) == 0 && ft_strlen(content->cmd[0]) == 3)
		ft_pwd();
	if(ft_strncmp(content->cmd[0], "cd", 2) == 0 && ft_strlen(content->cmd[0]) == 2)
		ft_cd(content, env);
	if(ft_strncmp(content->cmd[0], "echo", 4) == 0 && ft_strlen(content->cmd[0]) == 4)
		ft_echo(content);
	if(ft_strncmp(content->cmd[0], "exit", 4) == 0 && ft_strlen(content->cmd[0]) == 4)
	{
		ft_free_content(content);
		ft_free_env(*env);
		exit(0);
	}
}

int	ft_is_built_in(t_content *content)
{
	if (!content->cmd[0])
		return (1);
	if((ft_strncmp(content->cmd[0], "export", 6) == 0 && ft_strlen(content->cmd[0]) == 6)
		||(ft_strncmp(content->cmd[0], "unset", 5) == 0 && ft_strlen(content->cmd[0]) == 5)
		||(ft_strncmp(content->cmd[0], "pwd", 3) == 0 && ft_strlen(content->cmd[0]) == 3)
		||(ft_strncmp(content->cmd[0], "cd", 2) == 0 && ft_strlen(content->cmd[0]) == 2)
		||(ft_strncmp(content->cmd[0], "exit", 4) == 0 && ft_strlen(content->cmd[0]) == 4))
		//||(ft_strncmp(content->cmd[0], "echo", 4) == 0 && ft_strlen(content->cmd[0]) == 4))
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

// void	ft_display_array_content(t_array *array)
// {
// 	int	i;

// 	i = 0;
// 	while(i < array->size)
// 	{
// 		printf("content[%d] : \n\n", i);
// 		printf("-----cmd-----|\n");
// 		ft_display_tab(array->content[i].cmd);
// 		printf("-------------|\n\n");
// 		printf("-----args----|\n");
// 		ft_display_tab(array->content[i].arg);
// 		printf("-------------|\n\n");
// 		//printf("infile : %d\n", array->content[i].infile);
// 		//printf("outfile : %d\n", array->content[i].outfile);
// 		i++;
// 	}
// }

void	ft_init_exec(t_list **env, t_array *array)
{
	int	i;
	t_expar expar;

	i = 0;
	//ft_display_array_content(array);
	while(i < array->size)
	{
		array->content[i].array_ptr = array;
		i++;
	}
	i = 0;
	if(array->size == 1 && ft_is_built_in(&array->content[i]) == 0)
		return(ft_is_built_in_dad(&array->content[i], env));
	else
	{
		expar.options = ct_get_paths(*env);
		if (!expar.options)
			return ;
		if (pipe(expar.pipe) == -1)
			return(ft_exec_failure(&expar, 1));
		while(i < array->size)
		{
			array->content[i].pos = i;
			array->content[i].size = array->size;
			array->content[i].pid = fork();
			if (array->content[i].pid == -1)
				ft_exec_failure(&expar, 2);
			if (array->content[i].pid == 0)
			{
				//ft_free_others(array, i);
				ft_exec_cmd(&expar, &array->content[i], env, array);
			}
			i++;
		}
		//printf("array.size = %d\n", array->size);
		ft_wait_pid(array);
		close(expar.pipe[0]);
		close(expar.pipe[1]);
 		ft_free_tab(expar.options);
	}
}

