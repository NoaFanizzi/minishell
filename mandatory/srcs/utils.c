/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:18:22 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/20 15:40:40 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_display_tab(char **tab)
{
	size_t	i;

	i = 0;
	if(!tab)
		return;
	while(tab[i])
	{
		ft_putstr_fd(tab[i], STDOUT_FILENO);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	//printf("tab[0] = %s\n", tab[0]);
	if(tab == NULL || tab[0] == NULL)
		return;
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

void	ft_free_files(t_content *content)
{
	size_t	i;

	if (!content || !content->files)
		return;

	i = 0;
	while (content->files[i].eof)
	{
		free(content->files[i].eof);
		content->files[i].eof = NULL;
		i++;
	}
	free(content->files);
	content->files = NULL;
}

void ft_free_array_content(t_array *array)
{
    int i;
    i = 0;

    if (!array || !array->content)
		return;
//	printf("array->size = %d\n", array->size);
    while (i < array->size)
    {
		//free_command(array->content[i].cmd_splitted);
		if(array->content[i].cmd)
        	ft_free_tab(array->content[i].cmd);
		if(array->content[i].arg)
			ft_free_tab(array->content[i].arg);
		if(array->content[i].files)
			ft_free_files(&array->content[i]);
		if(array->content[i].hdoc)
			ft_free_hdoc(array->content[i].hdoc);
		if (array->content[i].h_fd != (-2))
			close(array->content[i].h_fd);
        i++;
    }
    free(array->content);
}


void	ft_free_content(t_content *content)
{
	if(content->cmd)
		ft_free_tab(content->cmd);
	if(content->arg)
		ft_free_tab(content->arg);
	free_command(content->cmd_splitted);
	if(content->files)
		free(content->files);
	free(content);
}