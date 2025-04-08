/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:39:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/08 14:20:42 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_in_base(t_var *var, t_export *temp)
{
	size_t	i;
	size_t	pos;

	while(i < var->export_size)
	{
		if(ft_strncmp(temp->var, var->export->var, ft_strlen(temp)) == 0)
			return(0);
		i++;
	}
	return(1);
}

void	ft_get_var(t_export *temp, t_content *content)
{
	char* temp_value;
	size_t	i;
	size_t pos;
	
	i = 0;
	pos = ft_strrchr(content->arg, 61);
	temp->var = ft_calloc((i + 1), sizeof(char));
	while(i < pos)
	{
		temp->var[i] = content->arg[i];
		i++;
	}
	temp->var[i] = '\0';
	pos++;
	if(content->arg[pos] == '\0')
	{
		temp->status = 0;
		return;
	}
	temp_value = ft_strdup(&content->arg[pos]);
	temp->value = ft_atoi(temp_value);
	free(temp_value);
}

void	ft_add_new_exports(t_var *var, t_export *temp)
{
	size_t	i;
	
	t_export *new_export_var;

	i = 0;
	new_export_var = ft_calloc((var->export_size + 1), sizeof(t_export));
	while(var->)
	

	
}

void	ft_export(t_var *var, t_content *content)
{
	//je check si c'est dans mes exports
	//si c'est dans mes exports je check si c'est un nouvel assignement de value
		//si c'est le cas, je l'ajoute dans ma variable d'envrionnement et je modfiei la value de la variable dasn l'export.
		//si c'est pas le cas, je check si y'a une value qui lui est assigne, je l'ajoute dans ma variable export et si y'en a une je l'ajoute a la variable d'envrionnement
	//si c'est pas dans mes exports je check si y'a une value qui est associee
		//si y'en a une je l'ajoute a ma variable d'envrionnement
		//si y'en a pas je l'ajoute a ma variable export
		//apparemment export ca combine les 2 au final

	t_export temp;

	ft_get_var(&temp, content); // je recupere mes values temporaires qui me permettront de chekc si c'est deja dans les variables export et env
	if(ft_check_if_in_base(var, &temp) == 0) // je check si c'est deja dans mes exports
	{
		ft_add_new_exports(var, &temp);
	}
	free(temp);
}
