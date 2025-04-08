/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:34:46 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/08 12:34:19 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_exec(t_var *var, t_array *array)
{
	int	i;
	t_expar expar;

	i = 0;
	expar.options = ct_get_paths(var);
	if (!expar.options)
		return ;
	if (pipe(expar.pipe) == -1)
		ft_exec_failure(&expar, 1);
	while(i < array->size)
	{
		array->content[i].pid = fork();
		if (array->content[i].pid == -1)
			ft_exec_failure(&expar, 2);
		if (array->content[i].pid == 0)
			ft_exec_cmd(&expar, &array->content[i], var);
		i++;
	}
	printf("array.size = %d\n", array->size);
	close(expar.pipe[0]);
	close(expar.pipe[1]);
	i = 0;
	while(i < array->size)
	{
		printf("i = %d\n", i);
		ft_free_content(&array->content[i]);
		i++;
	}
	free(array->content);
	ft_free_tab(expar.options);
}
