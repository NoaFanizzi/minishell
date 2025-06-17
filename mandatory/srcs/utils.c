/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:18:22 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/17 17:59:06 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_display_tab(char **tab)
{
	size_t	i;

	i = 0;
	//printf("//////////////////////\n");
	if(!tab)
		return;
	while(tab[i])
	{
		ft_putstr_fd(tab[i], STDOUT_FILENO);
		ft_putstr_fd("\n", 1);
		i++;
	}
	//printf("//////////////////////\n\n\n\n\n");
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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
void ft_free_array_content(t_array *array)
{
    int i;
    i = 0;
    if (!array || !array->content)
		return;
    while (i < array->size)
    {
		//free_command(array->content[i].cmd_splitted);
        ft_free_tab(array->content[i].cmd);
		ft_free_tab(array->content[i].arg);
		if(array->content[i].files)
			free(array->content[i].files);
        i++;
    }
    free(array->content);
}


void	ft_free_content(t_content *content)
{
	ft_free_tab(content->cmd);
	ft_free_tab(content->arg);
	free_command(content->cmd_splitted);
	if(content->files)
		free(content->files);
	free(content);
}