/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:13:15 by nbodin            #+#    #+#             */
/*   Updated: 2025/06/11 15:02:06 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



size_t	count_redir(char **cmd)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (strncmp(cmd[i], "<", 1) == 0
			|| strncmp(cmd[i], ">", 1) == 0)
			count++;
		i++;
	}
	return (count);
}

//only valid input to read from is the rightmost one,
//only place where the output is going is the rightmost one
//altough there is nothing going in inbetween files when outputing, they are created
//that is not the case for inputs, if they dont exist they are not created
//also output files are created although the command doesnt work
void	figure_in_out_files(char **cmd, t_content *content)
{
	size_t	redir_count;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	redir_count = count_redir(cmd);
	content->files = NULL;
	if(redir_count == 0)
		return ;
	content->files = malloc(redir_count * sizeof(t_files));
	if (!content->files)
		return ;
	while (cmd[i])
	{
		if (strncmp(cmd[i], "<<", 2) == 0)
		{
			content->files[j].type = HDOC;
			content->files[j].index = i;
			j++;
		}
		else if (strncmp(cmd[i], ">>", 2) == 0)
		{
			content->files[j].type = APND;
			content->files[j].index = i;
			j++;
		}
		else if (strncmp(cmd[i], "<", 1) == 0)
		{
			content->files[j].type = IN;
			content->files[j].index = i;
			j++;
		}
		else if (strncmp(cmd[i], ">", 1) == 0)
		{
			content->files[j].type = OUT;
			content->files[j].index = i;
			j++;
		}
		i++;
	}
	if (j == 0)
		content->files = NULL;
}

size_t	count_cmd_opt(char **cmd, t_list *var)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (strncmp(cmd[i], "<", 1) == 0
			|| strncmp(cmd[i], ">", 1) == 0)
			i++;
		else if (ft_try(var, cmd[i]) == 0)
		{
			count++;
			i++;
			while (cmd[i])
			{
				if (cmd[i][0] == '-')
					count++;	
				i++;
			}
			break ;
		}
		i++;
	}
	return (count);
}

void	identify_cmd_opt(char **cmd, t_content *content, t_list *var)
{
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	size = count_cmd_opt(cmd, var);
	printf("SIZEEEEEEE = %zu\n", size);
	content->cmd = malloc((size + 1)* sizeof(char *));
	if (!content->cmd)
		return ;
	content->cmd[size] = NULL;
	while (cmd[i])
	{
		printf("I VALUEEEEE = %zu\n\n\n", i);
		if (strncmp(cmd[i], "<", 1) == 0
			|| strncmp(cmd[i], ">", 1) == 0)
			i++;
		else if (ft_try(var, cmd[i]) == 0)
		{
			content->cmd[j] = ft_strdup(cmd[i]);
			if (!content->cmd[j])
				return ;
			j++;
			i++;
			while (cmd[i])
			{
				if (cmd[i][0] == '-')
				{
					content->cmd[j] = ft_strdup(cmd[i]);
					if (!content->cmd[j])
						return ;
					j++;
				}
				i++;
			}
			break ;
		}
		i++;
	}
	content->cmd[j] = 0;

}



size_t	count_arg(char **cmd, t_list *var)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (strncmp(cmd[i], "<", 1) == 0
			|| strncmp(cmd[i], ">", 1) == 0)
			i++;
		else if (ft_try(var, cmd[i]) == 0)
		{
			i++;
			while (cmd[i])
			{
				if (cmd[i][0] == '-')
					i++;
				else if (strncmp(cmd[i], "<", 1) == 0
					|| strncmp(cmd[i], ">", 1) == 0)
					i += 2;
				else
				{
					count++;
					i++;
				}
			}
			break ;
		}
		i++;
	}
	return (count);
}

void	identify_arg(char **cmd, t_content *content, t_list *var)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	j = 0;
	count = count_arg(cmd, var);
	content->arg = malloc((count + 1) * sizeof(char *));
	if (!content->arg)
		return ;
	while (cmd[i])
	{
		if (strncmp(cmd[i], "<", 1) == 0
			|| strncmp(cmd[i], ">", 1) == 0)
			i++;
		else if (ft_try(var, cmd[i]) == 0)
		{
			i++;
			while (cmd[i])
			{
				if (cmd[i][0] == '-')
					i++;
				else if (strncmp(cmd[i], "<", 1) == 0
					|| strncmp(cmd[i], ">", 1) == 0)
					i += 2;
				else
				{
					content->arg[j] = ft_strdup(cmd[i]);
					if (!content->arg)
						return ;
					i++;
					j++;
				}
			}
			break ;
		}
		i++;
	}
	content->arg[j] = 0;
}

void	create_cmd_struct(char ***cmd_splitted, t_content *content, size_t cmd_index, t_list *var)
{
	figure_in_out_files(cmd_splitted[cmd_index], content);
	identify_cmd_opt(cmd_splitted[cmd_index], content, var);
	identify_arg(cmd_splitted[cmd_index], content, var);
}