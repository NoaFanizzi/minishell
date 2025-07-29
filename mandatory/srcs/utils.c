/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:18:22 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/29 08:29:43 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_tab(char **tab)
{
	size_t	i;

	i = 0;
	if(!tab)
	{
		printf("tab est nul\n");
		return;
	}
	while(tab[i])
	{
		printf("wtf\n");
		ft_putstr_fd(tab[i], STDOUT_FILENO);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if(tab == NULL || tab[0] == NULL)
		return;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
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

void	ft_close_array_fd(t_content *content)
{
	size_t	i;

	i = 0;
	if(content->stdin_saved != -2)
		close(content->stdin_saved);
	if(content->stdout_saved != -2)
		close(content->stdout_saved);
	if(!content->fd_array)
		return;
	while(i < content->hdoc_length)
	{
		if(content->fd_array[i] != -42 && content->fd_array[i] != -8)
			close(content->fd_array[i]);
		i++;
	}
	i = 0;
	// while(i < content->hdoc_length)
	// {
	// 	free(&content->fd_array[i]);
	// 	i++;
	// }
	free(content->fd_array);
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
		ft_close_array_fd(&array->content[i]);
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