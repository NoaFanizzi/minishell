/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:17:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/06/26 09:24:33 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
}

char	**ct_get_paths(t_list *var)
{
	//size_t	size;
	char	**options;
	t_env	*cpy;

	cpy = (t_env *)var->content;
	while (var && ft_strncmp(cpy->var, "PATH", 4) != 0)
	{
		var = var->next;
		cpy = (t_env *)var->content;
	}
	//size = ft_strlen(cpy->var);
	options = ft_split(cpy->arg, ':');
	//ft_display_tab(options);
	return (options);
	//TODO Protéger si on supprime juste PATH de la variable d'environnement
}

void	ft_close_all(t_content *content)
{
	ft_close_pipes(content->array_ptr);
	if(content && content->infile != -2) //  && content->input != 1
		close(content->infile);
	if(content && content->outfile != -2) //  && content->output != 0
		close(content->outfile);
}

size_t	ft_tablen(char **tab)
{
	size_t	i;

	i = 0;
	if(!tab)
		return(0);
	while(tab[i])
	{
		i++;
	}
	return(i);
}

char **ft_cmd_join(char **a, char **b)
{
	size_t	i;
	size_t	j;
	size_t	length;
	char **cmd;

	i = 0;
	j = 0;
	length = ft_tablen(a) + ft_tablen(b);
	cmd = ft_calloc(length + 1, (sizeof (char *)));
	while(i < ft_tablen(a))
	{
		cmd[i] = ft_strdup(a[i]);
		i++;
	}
	while(j < ft_tablen(b))
	{
		cmd[i] = ft_strdup(b[j]);
		i++;
		j++;
	}
	//ft_display_tab(cmd);
	if(a)
		ft_free_tab(a);
	if(b)
		ft_free_tab(b);
	return(cmd);
	
}

// int	main(int argc, char **argv, char **env)
// {
// 	size_t	i;
// 	t_expar	expar;
// 	int		exit_status;

// 	i = 0;
// 	exit_status = 0;
// 	if (argc != 5)
// 		exit(0);
// 	if (!(argv[2]) || !(argv[3]))
// 		exit(127);
// 	if (!*env)
// 		return (127);
// 	pipex(argv, env, &expar);
// 	waitpid(expar.pid_1, &exit_status, 0);
// 	waitpid(expar.pid_2, &exit_status, 0);
// 	return (WEXITSTATUS(exit_status));
// }