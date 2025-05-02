/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/05/02 09:23:25 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

//check cases when there is one commnad, or nothing or idk but you understood

char	***parse_command(char *line, char **env)
{	
	char 	**command = NULL;
	char	***cmd_splitted = NULL;
	int		k;
	int		i;

	k = 0;
	command = quotes_splitting(command, line);
	free(line);
	if (!command)
		return (NULL);//error
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	printf("\n\n");
	command = space_splitting(command);
	if (!command)
		return (NULL);//error
	k = 0;
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	printf("\n\n");
	
	command = meta_splitting(command);
	if (!command)
		return (NULL);//error
	k = 0;
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	
	quotes_removal(command);
	
	if (!command)
		return (NULL);//error
	k = 0;
	while (command[k])
	{
		printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	//LEAKS DONE UNTIL THERE
	//NEED TO FREE COMMAND BUT NOT FOR NOW
	cmd_splitted = command_splitting(command);
	if (!cmd_splitted)
		return (NULL);
	printf("\n\n");
	k = 0;
	while (cmd_splitted[k])
	{
		i = 0;
		printf("\ncommand n%d\n", k + 1);
		while (cmd_splitted[k][i])
		{
			printf("word n%d : %s\n", i + 1, cmd_splitted[k][i]);
			i++;
		}
		k++;
	}
	printf("\n\n");
	k = 0;
	while (command[k])
	{
		if (ft_try(env, command[k]) == 0)
			printf("%s is a command\n", command[k]);
		k++;
	}
	free_words(command);
	return (cmd_splitted);
}


void	analyse_command(char ***cmd_splitted, t_array **array, char **env)
{
	size_t	cmd_index;
	size_t	struct_index;

	cmd_index = 0;
	struct_index = 0;
	while(cmd_splitted[cmd_index])
	{
		if (strncmp(cmd_splitted[cmd_index][0], "|", 1) != 0)
			(*array)->size++;
		cmd_index++;
	}
	(*array)->content = malloc(((*array)->size) * sizeof(t_content));
	cmd_index = 0;
	while(cmd_splitted[cmd_index])
	{
		if (strncmp(cmd_splitted[cmd_index][0], "|", 1) != 0)
		{
			create_cmd_struct(cmd_splitted, &(*array)->content[struct_index], cmd_index);
			//test
			size_t i = 0;
			size_t count = count_redir(cmd_splitted[cmd_index]);
			while (i < count)
			{
				printf("redir index n%d :\n", (*array)->content[struct_index].files[i].index + 1);
				printf("redir%d\n\n", (int)(*array)->content[struct_index].files[i].type + 1);
				i++;
			}
			//test			
			struct_index++;
		}
		cmd_index++;
	}
	
	return ;
}

t_content	*launch_shell(char **env)
{
	char	*line;
	char	***cmd_splitted;
	t_array	*array;
	
	array = malloc(sizeof(t_array));
	if (!array)
		return (NULL);
	array->size = 0;
	array->content = NULL;
	while (1)
	{
		line = readline("maxishell$ ");
		if (line == NULL)
			exit(0);
		cmd_splitted = parse_command(line, env);
		if (!cmd_splitted)
			return (NULL);
		analyse_command(cmd_splitted, &array, env);
	}
}
int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	launch_shell(env);
	return (0);
}