/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:13:15 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 00:28:56 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


size_t	count_redir(char **cmd)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (strncmp(cmd[i], "<", 1) == 0
			|| strncmp(cmd[i], ">", 1) == 0)
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

void figure_hdoc(char **cmd, t_content *content, int tab[2], size_t redir_count)
{
    content->files[tab[1]].type = HDOC;
    content->files[tab[1]].index = tab[0];
    content->files[tab[1]].size = redir_count;
    rem_and_shift(cmd[tab[0] + 1]);
    content->files[tab[1]].eof = ft_strdup(cmd[tab[0] + 1]);
    tab[1]++;
    tab[0]++;
}

void figure_append(char **cmd, t_content *content, int tab[2], size_t redir_count)
{
    content->files[tab[1]].type = APND;
    content->files[tab[1]].index = tab[0];
    content->files[tab[1]].size = redir_count;
    content->files[tab[1]].eof = NULL;
    rem_and_shift(cmd[tab[0] + 1]);
    tab[1]++;
    tab[0]++;
}

void figure_in(char **cmd, t_content *content, int tab[2], size_t redir_count)
{
    content->files[tab[1]].type = IN;
    content->files[tab[1]].index = tab[0];
    content->files[tab[1]].size = redir_count;
    content->files[tab[1]].eof = NULL;
    rem_and_shift(cmd[tab[0] + 1]);
    tab[1]++;
    tab[0]++;
}

void figure_out(char **cmd, t_content *content, int tab[2], size_t redir_count)
{
    content->files[tab[1]].type = OUT;
    content->files[tab[1]].index = tab[0];
    content->files[tab[1]].size = redir_count;
    content->files[tab[1]].eof = NULL;
    rem_and_shift(cmd[tab[0] + 1]);
    tab[1]++;
    tab[0]++;
}

void check_for_op(char **cmd, t_content *content, int tab[2], size_t redir_count)
{
    if (strncmp(cmd[tab[0]], "<<", 2) == 0)
        figure_hdoc(cmd, content, tab, redir_count);
    else if (strncmp(cmd[tab[0]], ">>", 2) == 0)
        figure_append(cmd, content, tab, redir_count);
    else if (strncmp(cmd[tab[0]], "<", 1) == 0)
        figure_in(cmd, content, tab, redir_count);
    else if (strncmp(cmd[tab[0]], ">", 1) == 0)
        figure_out(cmd, content, tab, redir_count);
    else
        tab[0]++;
}

void figure_in_out_files(char **cmd, t_content *content)
{
    size_t redir_count;
    int tab[2] = {0, 0}; // tab[0] = i, tab[1] = j

    redir_count = count_redir(cmd);
    content->redir_count = redir_count;
    content->files = NULL;
    if (redir_count == 0)
        return ;
    content->files = ft_calloc((redir_count + 1), sizeof(t_files));
    if (!content->files)
        return ;
    while (cmd[tab[0]])
        check_for_op(cmd, content, tab, redir_count);
    if (tab[1] == 0)
        content->files = NULL;
}

size_t	count_cmd_opt(char **cmd)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (find_command_name(cmd, &i))
		count++;
	//printf("count : %zu\n", count);
	i++;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
			count++;
		else if (strncmp(cmd[i], "<", 1) != 0
		|| strncmp(cmd[i], ">", 1) != 0)
			break ;
		i++;
	}
	return (count);
}

void	assign_cmd_and_opt(char **cmd, t_content *content)
{
	size_t i = 0, j = 0;

	content->cmd[j] = ft_strdup(find_command_name(cmd, &i));
	if (!content->cmd[j])
		return ;
	rem_and_shift(content->cmd[j]);
	j++;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
			content->cmd[j++] = ft_strdup(cmd[i]);
		else if (strncmp(cmd[i], "<", 1) != 0 && strncmp(cmd[i], ">", 1) != 0)
			break ;
		i++;
	}
	content->cmd[j] = NULL;
}

void	identify_cmd_opt(char **cmd, t_content *content)
{
	size_t	size;

	size = count_cmd_opt(cmd);
	if (size == 0)
	{
		content->cmd = NULL;
		return ;
	}
	content->cmd = ft_calloc(size + 1, sizeof(char *));
	if (!content->cmd)
		return ;
	assign_cmd_and_opt(cmd, content);
}


char	*find_command_name(char **cmd, size_t *i)
{
	while (cmd[*i])
	{
		if ((strncmp(cmd[*i], "<", 1) == 0 || strncmp(cmd[*i], ">", 1) == 0))
		{
			if (!cmd[*i + 1] || !cmd[*i + 2])
				return (NULL);
			*i += 2;
		}
		else if (is_var_assign(cmd[*i]))
		{
			(*i)++;
		}
		else
			return (cmd[*i]);
	}
	return (NULL);
}

int	is_var_assign(char *str)
{
    size_t i;

	i = 0;
    if (!str || (!ft_isalpha(str[i]) && str[i] != '_'))
        return (0);
    while (ft_isalnum(str[i]) || str[i] == '_')
        i++;
    if (str[i] != '=')
        return (0);
    if (str[i + 1] == '\0')
        return (0);
    return (1);
}

size_t skip_opt_and_redirs(char **cmd, size_t start)
{
    while (cmd[start])
    {
        if (cmd[start][0] == '-')
            start++;
        else if (ft_strncmp(cmd[start], "<", 1) == 0
              || ft_strncmp(cmd[start], ">", 1) == 0)
            start += 2;
        else
            break;
    }
    return start;
}

size_t count_real_args(char **cmd, size_t start)
{
    size_t count = 0;

    while (cmd[start])
    {
        if (ft_strncmp(cmd[start], "<", 1) == 0
         || ft_strncmp(cmd[start], ">", 1) == 0)
            start += 2;
        else
        {
            count++;
            start++;
        }
    }
    return count;
}

size_t count_arg(char **cmd)
{
    size_t i = 0;

    if (!find_command_name(cmd, &i))
        return 0;

    i++; // move past command name
    i = skip_opt_and_redirs(cmd, i);
    return count_real_args(cmd, i);
}

void fill_args(char **cmd, size_t start, char **arg)
{
    size_t j = 0;

    while (cmd[start])
    {
        if (ft_strncmp(cmd[start], "<", 1) == 0
         || ft_strncmp(cmd[start], ">", 1) == 0)
            start += 2;
        else
        {
            arg[j] = ft_strdup(cmd[start]);
            if (!arg[j])
                return;
            rem_and_shift(arg[j]);
            j++;
            start++;
        }
    }
    arg[j] = NULL;
}

void identify_arg(char **cmd, t_content *content)
{
    size_t i = 0;
    size_t count;

    count = count_arg(cmd);
    if (count == 0)
    {
        content->arg = NULL;
        return;
    }

    content->arg = ft_calloc(count + 1, sizeof(char *));
    if (!content->arg)
        return;

    if (!find_command_name(cmd, &i))
    {
        free(content->arg);
        content->arg = NULL;
        return;
    }

    i++; // skip command name
    i = skip_opt_and_redirs(cmd, i);
    fill_args(cmd, i, content->arg);
}


void	create_cmd_struct(char ***cmd_splitted, t_content *content, size_t cmd_index)
{
	figure_in_out_files(cmd_splitted[cmd_index], content);
	identify_cmd_opt(cmd_splitted[cmd_index], content);
	identify_arg(cmd_splitted[cmd_index], content);
	content->pos = cmd_index;
	content->cmd_splitted = cmd_splitted;
}