/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:58:04 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/26 14:33:22 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_env(char **env, t_env *cpy)
{
	size_t	i;

	i = 0;
	while(env[i])
		i++;
	cpy->var = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(env[i])
	{
		cpy->var[i] = ft_strdup(env[i]);
		i++;
	}
	cpy->var[i] = 0;
}

void	ft_display_env(char **tab)
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
