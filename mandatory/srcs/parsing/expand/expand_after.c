/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_after.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:49:16 by nbodin            #+#    #+#             */
/*   Updated: 2025/08/20 10:02:57 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_after(char *cmd, size_t i)
{
	int		in_squote;
	int		in_dquote;
	size_t	j;

	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (cmd[j] && j <= i)
	{
		if (!in_dquote && cmd[j] == '\'')
			in_squote = !in_squote;
		else if (!in_squote && cmd[j] == '"')
			in_dquote = !in_dquote;
		j++;
	}
	if (in_squote || in_dquote)
		return (0);
	if (!cmd[j])
		return (0);
	if (cmd[j] == '\'' || cmd[j] == '"')
		return (1);
	return (0);
}

int	is_not_after_hdoc(char *cmd, size_t var_index)
{
	size_t	i;
	size_t	len;
	int		in_squote;
	int		in_dquote;

	i = 0;
	len = ft_strlen(cmd);
	in_squote = 0;
	in_dquote = 0;
	while (i < len)
	{
		handle_quote_state(&in_squote, &in_dquote, cmd, &i);
		if (!in_squote && !in_dquote && cmd[i] == '<' && cmd[i + 1] == '<')
		{
			i += 2;
			while (cmd[i] && ft_isspace(cmd[i]))
				i++;
			if (track_var_in_del(cmd, &i, var_index) == 0)
				return (0);
		}
		else
			i++;
	}
	return (1);
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

void	skip_redir_spaces(char *cmd, size_t *i)
{
	while (cmd[*i] && (cmd[*i] == '>' || cmd[*i] == '<'))
		(*i)++;
	while (cmd[*i] && ft_isspace(cmd[*i]))
		(*i)++;
}

int	is_after_great(char *cmd, size_t var_index)
{
	size_t	i;
	int		in_squote;
	int		in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	if (!cmd[i])
		return (0);
	while (cmd[i])
	{
		handle_quote_state(&in_squote, &in_dquote, cmd, &i);
		if (!in_squote && !in_dquote && (cmd[i] == '>' || cmd[i] == '<'))
		{
			skip_redir_spaces(cmd, &i);
			if (i == var_index)
				return (1);
			track_quotes_until_meta(&in_squote, &in_dquote, cmd, &i);
		}
		else if (cmd[i])
			i++;
	}
	return (0);
}
