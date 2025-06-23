/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:39:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/23 18:01:44 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_in_base(t_list *env, char *str)
{
	size_t	i;
	size_t	link;
	t_env *cpy;

	i = 0;
	link = 0;
	while(str[i] && str[i] != '=')
		i++;
	while(env)
	{
		cpy = (t_env *)env->content;
		if((ft_strncmp(cpy->var, str, i) == 0)
			&& (ft_strlen(cpy->var) == i))
			return(link);
		env = env->next;
		link++;
	}
	return(-1);
}

// void	ft_get_var(t_export *temp, t_content *content)
// {
// 	char *temp_value;
// 	int	i;
// 	int pos;
	
// 	i = 0;
// 	pos = ft_is_chr(content->arg[i], 61);
// 	temp->var = ft_calloc((i + 1), sizeof(char));
// 	while(i < pos)
// 	{
// 		temp->var[i] = content->arg[i];
// 		i++;
// 	}
// 	temp->var[i] = '\0';
// 	pos++;
// 	if(content->arg[pos] == '\0')
// 	{
// 		temp->status = 0;
// 		return;
// 	}
// 	temp_value = ft_strdup(&content->arg[pos]);
// 	temp->value = ft_atoi(temp_value);
// 	free(temp_value);
// }

int	ft_is_a_value(char *str)
{
	size_t	i;

	i = 0;
	// if(str[i] == '=')
	// 	return(1);
	while(str[i])
	{
		if(str[i] == '=')
			return(1);
		i++;
	}
		
	// if(str[i] == '=')
	// 	i++;
	if(str[i] == '\0')
		return(0);
	return(0);
}

int	ft_is_chr(char *str, char c)
{
	size_t	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return(i);
		i++;
	}
	return(-1);
}


// void	ft_display_export(t_list **env)
// {
// 	size_t	i;
// 	size_t	j;
// 	char **env_converted;
// 	t_env *cpy;
	
// 	while(env)
// 	{
		
// 	}

// 	i = 0;
	
// }

int	ft_init_export(t_list **env, t_content *content, size_t	i)
{
	t_env *link;
	int	temp;
	t_list *current;
	int	pos;


	// if(content->arg = NULL)
	// {
	// 	ft_display_export(env);
	// 	return(0);
	// }
	pos = ft_check_if_in_base(*env, content->arg[i]); // ça me return la position de où c'est dans la liste
	if(pos == -1) // ca veut dire que c'etait pas dedans
	{
		link = ft_add_new_link(content->arg[i]);
		ft_lstadd_back(env, ft_lstnew(link));
		if(link->arg != NULL)
			link->exp = 1;
	}
	else //ca veut dire que c'etait deja dedans
	{
		current = *env;
		while(pos > 0)
		{
			current = current->next;
			pos--;
		}
		link = (t_env *)current->content;
		if(link->arg == NULL) //si y'avait pas de value assigned a la variable
		{
			if(ft_is_a_value(content->arg[i]) == 1) //si y'a une value assigned a la variable qu'on est en train d'export
			{
				free(link->var);
				free(link->arg);
				free(link->op);
				//free(link);
				link = ft_add_new_link(content->arg[i]);
			}
		}
		else if(link->arg != NULL) // y'avait deja une value assigned
		{
			if(ft_is_a_value(content->arg[i]) == 1) //si y'a une value assigned a la variable qu'on est en train d'export
			{
				temp = ft_is_chr(content->arg[i], '=');
				temp++;
				free(link->arg);
				link->arg = NULL;
				link->arg = ft_strdup(&content->arg[i][temp]);
				// if(temp != -1) // y'a un +
				// {
				// }
				// else
				// {
				// 	pos = ft_is_chr(content->arg[i], '='); //TODO la fonction elle marche pas apparemment
				// 	free(link->arg);
				// 	link->arg = ft_strdup(&content->arg[i][pos]);
				// }
			}
		}
		//ft_free_content(content);
		// free(content->arg);
		// free(content->cmd);
	}
	return(0);
}
int	ft_export(t_list **env, t_content *content)
{
	size_t	i;

	i = 0;
	while(content->arg[i])
	{
		ft_init_export(env, content, i);
		i++;
	}
	return(0);
}
