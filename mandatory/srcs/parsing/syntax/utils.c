/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:18:22 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/06 21:15:38 by nofanizz         ###   ########.fr       */
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

void	ft_free_files(t_content *content)
{
	size_t	i;

	if (!content || !content->files)
		return ;
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

// void	ft_close_array_fd(t_content *content)
// {
// 	size_t	i;

// 	i = 0;
// 	if (content->stdin_saved != -2)
// 		close(content->stdin_saved);
// 	if (content->stdout_saved != -2)
// 		close(content->stdout_saved);
// 	if (!content->fd_array)
// 		return ;
// 	printf("content->hdoc_length = %zu\n", content->hdoc_length);
// 	while (i < content->hdoc_length)
// 	{
// 		if (content->fd_array[i] != -42 && content->fd_array[i] != -8)
// 			close(content->fd_array[i]);
// 		i++;
// 	}
// 	i = 0;
// 	free(content->fd_array);
// }

void	ft_close_array_fd(t_content *content, size_t pos)
{
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	if (content->stdin_saved != -2)
		close(content->stdin_saved);
	if (content->stdout_saved != -2)
		close(content->stdout_saved);
	size = content->array_ptr->size;
	while (j < size)
	{
		if (j != pos && content[0].array_ptr->content[j].fd_array != NULL)
		{
			while (i < content->array_ptr->content[j].hdoc_length)
			{
				if (content->array_ptr->content[j].fd_array[i] != -42
					&& content->array_ptr->content[j].fd_array[i] != -8)
				{
					close(content->array_ptr->content[j].fd_array[i]);
					content->array_ptr->content[j].fd_array[i] = -42;
				}
				i++;
			}
		}
		i = 0;
		j++;
	}
	if(content[i].fd_array)
		free(content[i].fd_array);
	content[i].fd_array = NULL;
}

void	ft_free_array_content(t_array *array)
{
	size_t	i;

	i = 0;
	if (!array || !array->content)
		return ;
	ft_close_array_fd(&array->content[i], -1);
	while (i < array->size)
	{
		if (array->content[i].cmd)
			ft_free_tab(array->content[i].cmd);
		if (array->content[i].arg)
			ft_free_tab(array->content[i].arg);
		if (array->content[i].files)
			ft_free_files(&array->content[i]);
		if (array->content[i].hdoc)
			ft_free_hdoc(array->content[i].hdoc);
		if (array->content[i].h_fd != (-2))
			close(array->content[i].h_fd);
		i++;
	}
	free(array->content);
}

void	ft_free_content(t_content *content)
{
	if (content->cmd)
		ft_free_tab(content->cmd);
	if (content->arg)
		ft_free_tab(content->arg);
	free_command(content->cmd_splitted);
	if (content->files)
		free(content->files);
	free(content);
}
