/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:31:17 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/31 18:11:17 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote_state(int *in_dquote, int *in_squote, char *cmd, size_t *i)
{
	if (!(*in_dquote) && cmd[*i] == S_QUOTE)
	{
		*in_squote = !(*in_squote);
		(*i)++;
	}
	else if (!(*in_squote) && cmd[*i] == D_QUOTE)
	{
		*in_dquote = !(*in_dquote);
		(*i)++;
	}
}

void	skip_spaces(char *cmd, size_t *i, int *spaced_after)
{
	while (cmd[*i] && ft_isspace(cmd[*i]))
	{
		*spaced_after = 1;
		(*i)++;
	}
}

int	check_new_redir_seq(char *cmd, size_t *i, int spaced_after, char op)
{
	if (cmd[*i] == '>' || cmd[*i] == '<' || cmd[*i] == '|')
	{
		if (spaced_after || cmd[*i] != op)
		{
			if (spaced_after && cmd[*i + 1] && cmd[*i + 1] == cmd[*i])
			{
				ft_putstr_fd("maxishell: syntax error near unexpected token `", 2);
				ft_putchar_fd(cmd[*i], 2);
				ft_putchar_fd(cmd[*i], 2);
				ft_putstr_fd("\n", 2);
			}
			else
			{
				ft_putstr_fd("maxishell: syntax error near unexpected token", 2);
				ft_putchar_fd(cmd[*i], 2);
				ft_putstr_fd("\n", 2);
			}
			return (1);
		}
	}
	return (0);
}

int	check_op_count(int op_count, char op)
{
	if (op_count >= 4)
	{
		ft_putstr_fd("maxishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(op, 2);
		ft_putchar_fd(op, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	else if (op_count == 3)
	{
		ft_putstr_fd("maxishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(op, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

int	check_pipe_end(char *cmd)
{
	size_t	i;

	i = ft_strlen(cmd) - 1;
	while (i > 0 && ft_isspace(cmd[i]))
		i--;
	if (cmd[i] && cmd[i] == '|')
	{
		ft_putstr_fd("maxishell: syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}
