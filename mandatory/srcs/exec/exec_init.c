/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:34:46 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/17 18:29:42 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_built_in_dad(t_content *content, t_list **env)
{
	printf("content->cmd[0] = %s\n", content->cmd[0]);
	if(ft_strncmp(content->arg[0], "export", 6) == 0 && ft_strlen(content->arg[0]) == 6)
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
	//printf("CMDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD[0] = %s\n", content->cmd[0]);
	//printf("cmd[0] = %s", content->cmd[0]);
	if (!content->cmd[0])
		return (1);
	if((ft_strncmp(content->arg[0], "export", 6) == 0 && ft_strlen(content->arg[0]) == 6)
		||(ft_strncmp(content->cmd[0], "unset", 5) == 0 && ft_strlen(content->cmd[0]) == 5)
		||(ft_strncmp(content->cmd[0], "pwd", 3) == 0 && ft_strlen(content->cmd[0]) == 3)
		||(ft_strncmp(content->cmd[0], "cd", 2) == 0 && ft_strlen(content->cmd[0]) == 2)
		||(ft_strncmp(content->cmd[0], "exit", 4) == 0 && ft_strlen(content->cmd[0]) == 4))
		//||(ft_strncmp(content->cmd[0], "echo", 4) == 0 && ft_strlen(content->cmd[0]) == 4))
		return(0);
	return(1);
}

void	ft_wait_pid(t_array *array)
{
	int	i;
	int status;

	i = 0;
	status = 0;
	while(i < array->size)
	{
		waitpid(array->content[i].pid, &status, 0);
		i++;
	}
}

// void	ft_free_others(t_array *array, int pos)
// {
// 	// int	i;

// 	// i = 0;
// 	// while(i < array->size)
// 	// {
// 	// 	if(i == pos)
// 	// 		i++;
// 	// 	ft_free_content(&array->content[i]);
// 	// 	i++;
// 	// }
// }

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
			ft_exec_failure(&expar, 1);
		while(i < array->size)
		{
			array->content[i].pos = i;
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
	//free(array->content);
	//ft_free_array_content(array);
}

