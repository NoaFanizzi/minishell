/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:39:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/28 14:16:29 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_in_base(t_list *env, char *str)
{
	size_t	i;
	size_t	link;
	t_env	*cpy;

	i = 0;
	link = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (env)
	{
		cpy = (t_env *)env->content;
		if ((ft_strncmp(cpy->var, str, i) == 0) && (ft_strlen(cpy->var) == i))
			return (link);
		env = env->next;
		link++;
	}
	return (-1);
}

int	ft_is_not_already_inside(t_content *content, size_t i)
{
	t_env	*link;

	link = ft_add_new_link(content->arg[i], content->array_ptr); // PROTECTED
	if (!link)
	{
		(void)i;
		content->array_ptr->p_exit_status = 1;
		ft_open_error(content, "link malloc");
		return (1);
	}
	if (ft_lstadd_back(content->env, ft_lstnew(link)) == 1)
	{
		content->array_ptr->p_exit_status = 1;
		ft_open_error(content, "link malloc");
		return (1);
	}
	if (link->arg != NULL)
		link->exp = 1;
	return (0);
}

int	ft_is_already_inside(t_content *content, int pos, size_t i)
{
	t_list	*current;
	t_env	*link;

	current = *content->env;
	while (pos > 0)
	{
		current = current->next;
		pos--;
	}
	link = (t_env *)current->content;
	if (ft_is_a_value(content->arg[i]) == 1)
	{
		free(link->arg);
		if (fill_env_arg(&link, content->arg[i], 0) == 1)
		{
			ft_open_error(content, NULL);
			return (1);
		}
	}
	return (0);
}

int	ft_init_export(t_list **env, t_content *content, size_t i)
{
	int	pos;

	if (ft_check_var_validity(content->arg[i]) == 1)
	{
		ft_putstr_fd("maxishell: export: `", STDERR_FILENO);
		ft_putstr_fd(content->arg[i], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		content->error_code = 1;
		return (1);
	}
	pos = ft_check_if_in_base(*env, content->arg[i]);
	if (pos == -1)
	{
		if (ft_is_not_already_inside(content, i) == 1)
			return (1);
	}
	else // ca veut dire que c'etait deja dedans
	{
		if (ft_is_already_inside(content, pos, i) == 1)
			return (1);
	}
	content->error_code = 0;
	return (0);
}

int	ft_export(t_list **env, t_content *content)
{
	size_t	i;
	t_list	*cpy;

	i = 0;
	if (content->arg == NULL)
	{
		cpy = dup_env_list(*env); // PROTECTED
		if (!cpy)
		{
			content->error_code = 1;
			ft_dup2_pb(content, "cpy");
			return (1);
		}
		content->error_code = 0;
		ft_display_export(cpy);
		return (0);
	}
	while (content->arg[i])
	{
		if (ft_init_export(env, content, i) == 1)
			return (0);
		i++;
	}
	content->error_code = 0;
	return (0);
}
