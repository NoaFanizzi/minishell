/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:17:56 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/30 02:14:53 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_many_numbers(t_content *content)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 1;
	count = 0;
	while (content->cmd[i])
	{
		j = 0;
		while (content->cmd[i][j])
		{
			if (content->cmd[i][j] >= '0' && content->cmd[i][j] <= '9')
				j++;
			else
				break ;
		}
		if (j == ft_strlen(content->cmd[i]))
			count++;
		i++;
	}
	return (count);
}

int	check_long_min_max(char *str, size_t *i)
{
	if (str[0] == '-')
	{
		if (ft_strcmp("-9223372036854775808", &str[0]) > 0
			&& ft_strlen(&str[*i]) >= 21)
			return (1);
		*i += 1;
	}
	else
	{
		if (str[0] == '+')
			*i += 1;
		if (ft_strcmp("9223372036854775807", &str[*i]) > 0
			&& ft_strlen(&str[*i]) >= 20)
			return (1);
	}
	return (0);
}

void	ft_display_int_array(int *array)
{
	size_t	i;

	i = 0;
	while (i < FD_SETSIZE)
	{
		printf("array[i] = %d\n", array[i]);
		i++;
	}
}

void	ft_fill_array(int *tab)
{
	size_t	i;

	i = 0;
	while (i < FD_SETSIZE)
	{
		tab[i] = -8;
		i++;
	}
}

void	check_directory_before_exec(t_content *content)
{
	struct stat	sb;

	if (stat(content->cmd[0], &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode) == 1)
		{
			ft_putstr_fd("maxishell: ", STDERR_FILENO);
			ft_putstr_fd(content->cmd[0], STDERR_FILENO);
			ft_putendl_fd(": is a directory", STDERR_FILENO);
			content->error_code = 126;
			ft_exit(content);
		}
	}
}
