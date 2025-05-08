/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:18:22 by nofanizz          #+#    #+#             */
/*   Updated: 2025/05/08 16:36:54 by nbodin           ###   ########lyon.fr   */
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
    int i;
	int	j;

	i = 0;
    if (!array || !array->content)
        return;
    while (i < array->size)
    {
		j = 0;
		while (array->content[i].cmd[j])
			free(array->content[i].cmd[j++]);
		free(array->content[i].cmd);
		j = 0;
		while (array->content[i].arg[j])
			free(array->content[i].arg[j++]);
		free(array->content[i].arg);
		
        if (array->content[i].infile != -2 && array->content[i].infile != -3)
            close(array->content[i].infile);
        if (array->content[i].outfile != -2 && array->content[i].infile != -3)
            close(array->content[i].outfile);
        i++;
    }
    free(array->content);
    array->content = NULL;
	array = NULL;
}

void	ft_free_content(t_content *content)
{
	    free(content->cmd[0]);
        free(content->cmd[1]);
	    free(content->cmd[2]);
	    free(content->cmd[3]);
        
        free(content->cmd);
        free(content->arg);
        if (content->infile != -2)
            close(content->infile);
        if (content->outfile != -2)
            close(content->outfile);
		content = NULL;
}