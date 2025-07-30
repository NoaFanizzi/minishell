/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_great.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:38:04 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/30 10:44:18 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_after_great_var(char *cmd, size_t var_index)
{
	size_t	i;
	size_t	token_start;
	int		in_squote;
	int		in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	if (!cmd)
		return (0);
	while (i < ft_strlen(cmd))
	{
		handle_quote_state(&in_squote, &in_dquote, cmd, &i);
		if (!in_squote && !in_dquote && (cmd[i] == '>' || cmd[i] == '<'))
		{
			skip_redir_spaces(cmd, &i);
			token_start = i;
			track_quotes_until_meta(&in_squote, &in_dquote, cmd, &i);
			if (var_index >= token_start && var_index < i)
				return (1);
		}
		else
			i++;
	}
	return (0);
}
