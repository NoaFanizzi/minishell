/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:47:49 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 23:40:49 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_var_first_char(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

int	valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

void	skip_redir_spaces(char *cmd, size_t *i)
{
	while (cmd[*i] && (cmd[*i] == '>' || cmd[*i] == '<'))
		(*i)++;
	while (cmd[*i] && ft_isspace(cmd[*i]))
		(*i)++;
}

int	track_var_in_del(char *cmd, size_t *i, size_t var_index)
{
	int	in_squote;
	int	in_dquote;

	in_squote = 0;
	in_dquote = 0;
	while (cmd[*i])
	{
		if (*i == var_index)
			return (0);
		if (!in_dquote && cmd[*i] == '\'')
			in_squote = !in_squote;
		else if (!in_squote && cmd[*i] == '"')
			in_dquote = !in_dquote;
		if (!in_squote && !in_dquote && (ft_isspace(cmd[*i]) || cmd[*i] == '|'
				|| cmd[*i] == '<' || cmd[*i] == '>' || cmd[*i] == '\0'))
			break ;
		(*i)++;
	}
	return (1);
}

int copy_error_code(char *new_cmd, size_t *k, char *error_code)
{
    ft_strcpy(&new_cmd[*k], error_code);
    *k += ft_strlen(error_code);
    return (2);
}
