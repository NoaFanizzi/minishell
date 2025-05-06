/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:17:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/30 13:21:44 by nofanizz         ###   ########.fr       */
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
}

void	ft_close_all(t_expar *expar, t_content *content)
{
	close(expar->pipe[0]);
	close(expar->pipe[1]);
	if(content && content->infile != -2) //  && content->input != 1
		close(content->infile);
	if(content && content->outfile != -2) //  && content->output != 0
		close(content->outfile);
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