/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:17:19 by nofanizz          #+#    #+#             */
/*   Updated: 2025/04/08 12:22:24 by nofanizz         ###   ########.fr       */
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

char	**ct_get_paths(t_var *var)
{
	size_t	size;
	size_t	i;
	char	**options;

	i = 0;
	while (ft_strncmp(var->env[i], "PATH=", 5) != 0)
		i++;
	size = ft_strlen(var->env[i]);
	options = ft_split(var->env[i] + 5, ':');
	//ft_display_tab(options);
	return (options);
}

void	ft_close_all(t_expar *expar, t_content *content)
{
	close(expar->pipe[0]);
	close(expar->pipe[1]);
	if(content->input != -2) //  && content->input != 1
		close(content->input);
	if(content->output != -2) //  && content->output != 0
		close(content->output);
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