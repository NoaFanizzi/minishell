/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:17:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/15 14:48:25 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
}

char	**ct_get_paths(t_list *var, t_content *content)
{
	char	**options;
	t_env	*cpy;

	if(!var)
		return(NULL);
	cpy = get_env("PATH", var);
	if(cpy == NULL)
		return(NULL);
	options = ft_split(cpy->arg, ':');
	if(!options)
		ft_exit(content);
	return (options);
}

void	ft_close_all(t_content *content)
{
	ft_close_pipes(content->array_ptr);
	if((content && content->infile != -2)
		&&(content->infile != -1))
	{
		close(content->infile);
		content->infile = -2;
	}
	if((content && content->outfile != -2)
		&&(content->outfile != -1))
	{
		close(content->outfile);
		content->outfile = -2;
	}
	if(content->h_fd != -2 && content->h_fd != -1)
	{
		close(content->h_fd);
		content->h_fd = -2;
	}
	if(content->stdin_saved != -2 && content->stdin_saved != -1)
	{
		close(content->stdin_saved);
		content->stdin_saved = -2;
	}
	if(content->stdout_saved != -2 && content->stdout_saved != -1)
	{
		close(content->stdout_saved);
		content->stdout_saved = -2;
	}
}

size_t	ft_tablen(char **tab)
{
	size_t	i;

	i = 0;
	if(!tab)
		return(0);
	while(tab[i])
	{
		i++;
	}
	return(i);
}

char **ft_cmd_join(char **a, char **b)
{
	size_t	i;
	size_t	j;
	size_t	length;
	char **cmd;

	i = 0;
	j = 0;
	length = ft_tablen(a) + ft_tablen(b);
	cmd = ft_calloc(length + 1, (sizeof (char *)));
	while(i < ft_tablen(a))
	{
		cmd[i] = ft_strdup(a[i]);
		i++;
	}
	while(j < ft_tablen(b))
	{
		cmd[i] = ft_strdup(b[j]);
		i++;
		j++;
	}
	//ft_display_tab(cmd);
	if(a)
		ft_free_tab(a);
	if(b)
		ft_free_tab(b);
	return(cmd);
	
}


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
		if(array->content[i].arg[0])
		{
			printf("-----args----|\n");
			ft_display_tab(array->content[i].arg);
			printf("-------------|\n\n");
		}
		if(array->content[i].files)
		//printf("infile : %d\n", array->content[i].infile);
		//printf("outfile : %d\n", array->content[i].outfile);
		i++;
	}
}
