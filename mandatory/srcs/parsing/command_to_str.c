/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/06/24 16:51:54 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check cases when there is one commnad, or nothing or idk but you understood



char	***parse_command(char *line)
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
		//printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	//printf("\n\n");
	//EXPAND
	
	contiguous_quotes(&command);
	if (!command)
		return (NULL);
	k = 0;
	while (command[k])
	{
		//printf("Aword n%d : %s\n", k + 1, command[k]);
		k++;
	}
	//printf("\n\n");
	command = space_splitting(command);
	if (!command)
		return (NULL);//error
	k = 0;
	while (command[k])
	{
		//printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	//printf("\n\n");
	command = meta_splitting(command);
	if (!command)
	return (NULL);//error
	k = 0;
	while (command[k])
	{
		//printf("word n%d : %s\n", k + 1, command[k]);
		k++;
	}
	cmd_splitted = command_splitting(command);
	if (!cmd_splitted)
	return (NULL);
	//printf("\n\n");
	k = 0;
	while (cmd_splitted[k])
	{
		i = 0;
		//printf("\ncommand n%d\n", k + 1);
		if (!cmd_splitted[k][i])
		//printf("NULL\n");
		while (cmd_splitted[k][i])
		{
			//printf("word n%d : %s\n", i + 1, cmd_splitted[k][i]);
			i++;
		}
		k++;
	}
	free_words(command);
	return (cmd_splitted);
}

int    create_hdoc_struct(t_array *array, char **command)
{
    size_t    hdoc_count;
    size_t    i;
    
    i = 0;
    hdoc_count = 0;
    while (command[i])
    {
        if (ft_strncmp(command[i], "<<", 2) == 0)
        {
            hdoc_count++;
            i++;
        }
        i++;
    }
    if (hdoc_count == 0)
	{
		i = 0;
		while((int)i < array->size)
		{

			array->content[i].hdoc = NULL;
			i++;
		}
        return(0);
	}
    array->content->hdoc = malloc(hdoc_count * sizeof(t_heredocs));
    if (!array->content->hdoc)
        return(-1);
    i = 0;
    while (command[i])
    {
        if (ft_strncmp(command[i], "<<", 2) == 0)
        {
            if (command[i + 1][0] == S_QUOTE)
                array->content->hdoc[i].s_quoted = 1;
            else
                array->content->hdoc[i].s_quoted = 0;
            array->content->hdoc[i].text = NULL;
            array->content->hdoc[i].size = hdoc_count;
        }
        i++;
    }
	return(0);
}

void	analyse_command(char ***cmd_splitted, t_array *array, t_list *var)
{
	size_t	cmd_index;
	size_t	struct_index;

	cmd_index = 0;
	struct_index = 0;
	while(cmd_splitted[cmd_index])
	{
		if (cmd_splitted[cmd_index][0] && strncmp(cmd_splitted[cmd_index][0], "|", 1) != 0)
			 array->size++;
		cmd_index++;
	}
	array->content = malloc(( array->size) * sizeof(t_content));
	//check malloc
	cmd_index = 0;
	(void) var;
	while(cmd_splitted[cmd_index])
	{
		if (create_hdoc_struct(array, cmd_splitted[cmd_index]) == -1)
			return ;//need to see how to check that
		quotes_removal(cmd_splitted[cmd_index]);
		if (cmd_splitted[cmd_index][0] && strncmp(cmd_splitted[cmd_index][0], "|", 1) != 0)
		{
			create_cmd_struct(cmd_splitted, &array->content[struct_index], cmd_index);
			//test
			size_t i = 0;
			size_t count = count_redir(cmd_splitted[cmd_index]);
			while (i < count)
			{
				//printf("redir index n%d :\n",  array->content[struct_index].files[i].index + 1);
				//printf("redir%d\n\n", (int) array->content[struct_index].files[i].type + 1);
				i++;
			}
			i = 0;
			count = count_cmd_opt(cmd_splitted[cmd_index]);
			//("count_cmd_opt : %zu\n", count);
			while (i < count)
			{
				//printf("CMD n%lu:%s\n", i + 1,  array->content[struct_index].cmd[i]);
				i++;
			}
			i = 0;
			count = count_arg(cmd_splitted[cmd_index]);
			//printf("count_arg : %zu\n", count);
			while (i < count)
			{
				//printf("ARG n%lu:%s\n", i + 1,  array->content[struct_index].arg[i]);
				i++;
			}
			//test			
			struct_index++;
		}
		cmd_index++;
	}
	//free_command(cmd_splitted);TODOAttention gros problemes en vue
	fill_struct_size(array, struct_index);
	return ;
}


void    fill_struct_size(t_array *array, size_t struct_index)
{
	size_t i;
	
    i = 0;
    while (i < struct_index)
    {
		array->content[i].size = struct_index;
        //(array)->content[i].infile = -3;
        //(array)->content[i].outfile = -3;
        i++;
    }
}

void	launch_shell(t_list **var)
{
	char	*line;
	char	***cmd_splitted;
	t_array	array;
	//int i = 0;
	
	while (1)
	{
		line = readline("maxishell$ ");
		if (line == NULL)
		break;
		if (line)
		add_history(line);
		array.size = 0;
		array.content = NULL;
		cmd_splitted = parse_command(line);
		if (!cmd_splitted)
		return ;
		analyse_command(cmd_splitted, &array, *var);
		ft_init_exec(var, &array);
		//printf("\n");
		//i++;
		free_command(cmd_splitted);
		ft_free_array_content(&array);
		//break;
	}
}

// int	main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	launch_shell(env);
// 	return (0);
// }


//LUCAS
//overall need exit codes and error prints
//7 EXP
//8 EXP
//13
//14
//15 EXP
//16 EXP
//20 LAST EXIT CODE
//21 LAST EXIT CODE
//23 idk we ll see
//24-32 cmd ident - need a function to check if they are builtins so i can fill the struct
//33-38 same thing than export but for unset
//39-41 same thing with cd
