/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:22:44 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/27 18:12:34 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_content *content, t_list **env)
{
	(void)content;
	(void)env;
	// int	params;

	// params = 0;
	// content->error_code = 0;
	// if (ft_tablen(content->arg) > 1)
	// {
	// 	content->error_code = 1;
	// 	ft_putstr_fd("maxishell: cd: too many arguments\n", STDERR_FILENO);
	// 	return ;
	// }
	// if (ft_deal_with_dash(content, env, &params) == 2)
	// 	return ;
	// if (!content->arg)
	// {
	// 	if (ft_deal_with_wave(content, env, &params) == 2)
	// 		return ;
	// }
	// if (ft_access_dir(content) == 1)
	// 	return ;
	// if (ft_update_opwd(env) == 1)
	// 	return ;
	// if (ft_update_pwd(env, content) == 1)
	// 	return ;
	// if (params == 1)
	// 	ft_putendl_fd(content->arg[0], STDOUT_FILENO);
}
