/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:39:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/05/05 13:25:59 by nofanizz         ###   ########.fr       */
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

void	ft_get_var(t_export *temp, t_content *content)
{
	char *temp_value;
	int	i;
	int pos;
	
	i = 0;
	pos = ft_is_chr(content->arg, 61);
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

int	ft_is_a_value(char *str)
{
	size_t	i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if(str[i] == '=')
		i++;
	if(str[i] == '\0')
		return(1);
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

int	ft_export(t_list **env, t_content *content)
{
	t_env *link;
	char	*temp;
	t_list *current;
	int	pos;
	int	i;

	printf("----------------------export beginning------------------------\n");
	i = 0;
	pos = ft_check_if_in_base(*env, content->arg); // ça me return la position de où c'est dans la liste
	if(pos == -1) // ca veut dire que c'etait pas dedans
	{
		link = ft_add_new_link(content->arg);
		printf("link->var= %s\n", link->var);
		printf("link->op = %s\n", link->op);
		printf("link->arg= %s\n", link->arg);

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
			if(ft_is_a_value(content->arg) == 1) //si y'a une value assigned a la variable qu'on est en train d'export
			{
				free(link->var);
				free(link->arg);
				free(link->op);
				//free(link);
				link = ft_add_new_link(content->arg);
			}
		}
		else if(link->arg != NULL) // y'avait deja une value assigned
		{
			if(ft_is_a_value(content->arg) == 1) //si y'a une value assigned a la variable qu'on est en train d'export
			{
				if(ft_is_chr(content->arg, '+') != -1) // y'a un +
				{
					printf("chockbarrrrr\n");
					temp = ft_strjoin(link->arg, content->arg);
					free(link->arg);
					link->arg = ft_strdup(temp);
					free(temp);
				}
				else
				{
					pos = ft_is_chr(content->arg, '='); //TODO la fonction elle marche pas apparemment
					free(link->arg);
					printf("pos======%d\n", pos);
					printf("first leak = %s\n", &content->arg[pos]);
					printf("true arg = %s\n", content->arg);
					link->arg = ft_strdup(&content->arg[pos]);
				}
			}
		}
		printf("--------------aaaaaaaaaaaaaaaaaaaaaaaa---------------\n");
		//ft_free_content(content);
		// free(content->arg);
		// free(content->cmd);
	}
	printf("----------------------------------end----------------------------\n");
	return(0);
}
