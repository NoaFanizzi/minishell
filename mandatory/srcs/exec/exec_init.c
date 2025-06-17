/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:34:46 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/12 18:18:28 by nofanizz         ###   ########.fr       */
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
	if(ft_strncmp(content->cmd[0], "exit", 4) == 0 && ft_strlen(content->cmd[0]) == 4)
	{
		ft_free_content(content);
		ft_free_env(*env);
		exit(0);
	}
}

int	ft_is_built_in(t_content *content)
{
	printf("CMDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD[0] = %s\n", content->cmd[0]);
	if((ft_strncmp(content->cmd[0], "export", 6) == 0 && ft_strlen(content->cmd[0]) == 6)
		||(ft_strncmp(content->cmd[0], "unset", 5) == 0 && ft_strlen(content->cmd[0]) == 5)
		||(ft_strncmp(content->cmd[0], "pwd", 3) == 0 && ft_strlen(content->cmd[0]) == 3)
		||(ft_strncmp(content->cmd[0], "cd", 2) == 0 && ft_strlen(content->cmd[0]) == 2)
		||(ft_strncmp(content->cmd[0], "exit", 4) == 0 && ft_strlen(content->cmd[0]) == 4))
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

void	ft_init_exec(t_list **env, t_array *array)
{
	int	i;
	t_expar expar;

	i = 0;
	while(i < array->size)
	{
		array->content[i].array_ptr = array;
		i++;
	}
	i = 0;
	if(!array)
		return;
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
			array->content[i].pid = fork();
			if (array->content[i].pid == -1)
				ft_exec_failure(&expar, 2);
			if (array->content[i].pid == 0)
				ft_exec_cmd(&expar, &array->content[i], env);
			i++;
		}
		//printf("array.size = %d\n", array->size);
		close(expar.pipe[0]);
		close(expar.pipe[1]);
 		ft_free_tab(expar.options);
	}
	ft_wait_pid(array);
	//free(array->content);
	//ft_free_array_content(array);
}

