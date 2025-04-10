/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:18:22 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/10 16:26:57 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_display_tab(char **tab)
{
	size_t	i;

	i = 0;
	while(tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
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
    int i = 0;

    if (!array || !array->content)
        return;
    while (i < array->size)
    {
        free(array->content[i].cmd[0]);
        free(array->content[i].cmd[1]);
        free(array->content[i].cmd[2]);
        free(array->content[i].cmd[3]);
        free(array->content[i].cmd);
        free(array->content[i].arg);
        if (array->content[i].input != -2)
            close(array->content[i].input);
        if (array->content[i].output != -2)
            close(array->content[i].output);
        i++;
    }
    free(array->content);
    array->content = NULL;
}

void	ft_free_content(t_content *content)
{
	if(content->cmd != NULL)
		ft_free_tab(content->cmd);
}