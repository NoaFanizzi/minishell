/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:48:34 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/20 13:57:46 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_list *env)
{
	t_list	*current;
	t_env	*content;

	while (env)
	{
		current = env;
		env = env->next;
		content = (t_env *)current->content;
		free(content->var);
		free(content->op);
		free(content->arg);
		free(content);
		free(current);
	}
}

void	free_unlink(char **str)
{
	unlink(*str);
	free(*str);
}

void	ft_free_hdoc(t_heredocs *hdoc)
{
	size_t	i;
	size_t	count;

	i = 0;
	if (!hdoc)
		return ;
	count = hdoc[0].size;
	while (i < count)
	{
		ft_free_tab(hdoc[i].text);
		i++;
	}
	free(hdoc);
}

void	ft_exec_failure(t_expar *expar, int i)
{
	if (i == 1)
		perror("pipe");
	if (i == 2)
		perror("fork");
	free(expar->options);
	return ;
}

void	*ft_free_one_chain_element(t_env *env, t_array *array)
{
	//ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
	array->p_exit_status = 1;
	free(env->arg);
	free(env->op);
	free(env->var);
	free(env);
	return (NULL);
}
