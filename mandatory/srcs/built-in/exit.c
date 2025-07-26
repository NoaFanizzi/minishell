/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:57:47 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/26 20:24:02 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_arg_numeric(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-')
	{
		if (ft_strcmp(&str[0], "-9223372036854775808") < 0)
			return (1);
		i++;
	}
	else
	{
		if (str[0] == '+')
			i++;
		if (ft_strcmp(&str[i], "9223372036854775807") < 0)
			return (1);
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_is_last_arg_numeric(t_content *content)
{
	size_t	i;

	i = 1;
	while (content->cmd[i + 1])
		i++;
	if (ft_is_arg_numeric(content->cmd[i]) == 1)
		return (1);
	return (0);
}

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

int	ft_check_if_valid_exit(t_content *content)
{
	if (!content->cmd)
		return (0);
	content->cmd = ft_cmd_join(content->cmd, content->arg);
	content->arg = NULL;
	if ((ft_strcmp(content->cmd[0], "exit") == 0)
		&& (ft_tablen(content->cmd) > 1))
	{
		if (ft_is_arg_numeric(content->cmd[1]) == 1) // check pour le first
		{
			ft_putstr_fd("maxishell: exit: ", 1);
			ft_putstr_fd(content->cmd[1], 1);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			content->error_code = 2;
			return (0);
		}
		if (ft_is_many_numbers(content) > 1
			|| ft_is_last_arg_numeric(content) == 1)
		{
			ft_putstr_fd("maxishell: exit: too many arguments\n",
				STDERR_FILENO);
			content->error_code = 1;
			return (1);
		}
		content->error_code = ft_atoi(content->cmd[1]);
	}
	return (0);
}

void	ft_exit(t_content *content)
{
	int	error_code;
	int	validity_value;

	if (!content)
		exit(1);
	validity_value = ft_check_if_valid_exit(content);
	if (validity_value == 1 && content->array_ptr->size == 1)
		return ;
	error_code = get_right_error_code(content);
	if (content->env)
		ft_free_env(*(content->env));
	if (content->expar)
		ft_close_all(content);
	if (content->expar)
	{
		if (content->expar->options)
			ft_free_tab(content->expar->options);
		free(content->expar->path);
		free(content->expar);
	}
	if (content->cmd_splitted)
		free_command(content->cmd_splitted);
	if (content->array_ptr)
		ft_free_array_content(content->array_ptr);
	exit(error_code);
}
