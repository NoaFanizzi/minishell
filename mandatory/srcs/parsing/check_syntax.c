/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:49:36 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/28 13:36:53 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_redir(char *cmd, size_t *i)
{
	char	op;
	int		op_count;
	int		spaced_after;

	op = cmd[*i];
	op_count = 1;
	spaced_after = 0;
	(*i)++;
	while (cmd[*i] == op)
	{
		op_count++;
		(*i)++;
	}
	if (check_op_count(op_count, op))
		return (1);
	skip_spaces(cmd, i, &spaced_after);
	if (!cmd[*i])
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (check_new_redir_seq(cmd, i, spaced_after, op))
		return (1);
	return (0);
}

int	check_pipe_start(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] && ft_isspace(cmd[i]))
		i++;
	if (cmd[i] && cmd[i] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	check_consecutive_pipes(char *cmd, size_t *i)
{
	(*i)++;
	while (cmd[*i] && ft_isspace(cmd[*i]))
		(*i)++;
	if (cmd[*i] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	check_redir_pipes(char *cmd)
{
	size_t	i;
	int     in_squote;
	int     in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (cmd[i])
	{
		handle_quote_state(&in_dquote, &in_dquote, cmd, &i);
		if (!in_squote && !in_dquote && (cmd[i] == '>' || cmd[i] == '<'))
		{
			if (check_redir(cmd, &i))
				return (1);
		}
		else if (!in_squote && !in_dquote && cmd[i] == '|')
		{
			if (check_consecutive_pipes(cmd, &i))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_syntax(char *cmd)
{
	if (quotes_checker(cmd))
		return (1);
	if (check_pipe_start(cmd))
		return (1);
	if (check_redir_pipes(cmd))
		return (1);
	if (check_pipe_end(cmd))
		return (1);
	return (0);
}
