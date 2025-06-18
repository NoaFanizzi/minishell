/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_splitting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:46:29 by nbodin            #+#    #+#             */
/*   Updated: 2025/06/17 17:59:40 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_commands(char **command)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (command[i][0] == '|')
			count++;
		i++;
	}
	return (count + count + 1);
}

int		count_command_words(char **command)
{
	size_t	i;
	int	count;

	i = 0;
	count = 0;
	if (command[i] && command[i][0] == '|')
		return (1);
	while (command[i])
	{
		if (command[i][0] == '|')
			return (count);
		i++;
		count++;
	}
	return (count);
}

void	*free_command(char ***splitted)
{
	size_t	i;
	size_t	j;

	i = 0;
	if(!splitted)
		return(NULL);
	while ((splitted)[i])
	{
		j = 0;
		while ((splitted)[i][j])
		{
			free((splitted)[i][j]);
			j++;
		}
		free((splitted)[i]);
		i++;
	}
	free(splitted);
	splitted = NULL;
	return (NULL);
}

// void	*free_command(char ***splitted)
// {
// 	size_t	i;

// 	if (!splitted || !*splitted)
// 		return (NULL);
// 	i = 0;
// 	while ((*splitted)[i])
// 	{
// 		free((*splitted)[i]);  // free le tableau de char * (mais pas les chaînes individuelles ici)
// 		i++;
// 	}
// 	free(*splitted); // free le tableau de char **
// 	*splitted = NULL;
// 	return (NULL);
// }

// void *free_command(char ***splitted)
// {
//     size_t i;

//     if (!splitted || !*splitted)
//         return (NULL);
//     i = 0;
//     while ((*splitted)[i])
//     {
//         free((*splitted)[i]);  // Libère chaque chaîne (char *)
//         i++;
//     }
//     free(*splitted);  // Libère le tableau principal
//     *splitted = NULL;
//     return (NULL);
// }

// void	*free_command(char ***splitted)
// {
// 	size_t	i;

// 	if (!splitted || !*splitted)
// 		return (NULL);
// 	i = 0;
// 	while ((*splitted)[i])
// 	{
// 		free((*splitted)[i]);  // free le tableau de char * (mais pas les chaînes individuelles ici)
// 		i++;
// 	}
// 	free(*splitted); // free le tableau de char **
// 	*splitted = NULL;
// 	return (NULL);
// }





char	***init_splitted(char ***splitted, char **command)
{
	int		cmd_count;
	int		cmd_words_count;
	size_t	cmd_index;
	size_t	k;

	k = 0;
	cmd_index = 0;
	cmd_count = count_commands(command);
	splitted = malloc((cmd_count + 1) * sizeof(char **));
	if (!splitted)
		return (NULL);//malloc error
	while ((int)k < cmd_count)
	{
		cmd_words_count = count_command_words(&command[cmd_index]);
		cmd_index += cmd_words_count;
		splitted[k] = malloc((cmd_words_count + 1) * sizeof(char *));
		if (!splitted[k])
			return (free_command(splitted));//malloc error
		k++;
	}
	splitted[k] = 0;
	return (splitted);
}

char	***fill_splitted_command(char ***splitted, char **command)
{
	size_t	k;
	size_t	i;
	size_t	cmd_index;
	int	cmd_count;
	int		cmd_words_count;
	
	cmd_index = 0;
	cmd_count = count_commands(command);
	//printf("cmd_count ====== %d\n", cmd_count);
	k = 0;
	i = 0;
	
	while ((int)k < cmd_count)
	{
		cmd_words_count = count_command_words(&command[cmd_index]);
		i = 0;
		while ((int)i < cmd_words_count)
		{
			splitted[k][i] = ft_strdup(command[cmd_index + i]);
			if (!splitted[k][i])
				return (free_command(splitted));
			i++;
		}
		//printf("GOT HEREEEEEEE\n");
		cmd_index += cmd_words_count;
		splitted[k][i] = 0;
		k++;
	} 
	splitted[k] = 0;
	return (splitted);
}

char	***command_splitting(char **command)
{
	char	 ***splitted = NULL;
	
	splitted = init_splitted(splitted, command);
	if (!splitted)
		return (NULL);
	splitted = fill_splitted_command(splitted, command);
	if (!splitted)
		return (NULL);
	return (splitted);
}