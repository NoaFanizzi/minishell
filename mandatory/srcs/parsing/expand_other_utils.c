/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_other_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:51:25 by nbodin            #+#    #+#             */
/*   Updated: 2025/07/29 18:39:10 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_var_length(char *word)
{
	size_t	len;

	len = 0;
	while (word[len] && valid_var_char(word[len]))
		len++;
	return (len + 1);
}

char	*get_var_name(char *word)
{
	size_t	i;
	char	*var_name;

	i = 0;
	while (word[i] && valid_var_char(word[i]))
		i++;
	var_name = ft_substr(word, 0, i); // PROTECTED
	if (!var_name)
	{
		ft_putendl_fd("maxishell: malloc error", STDERR_FILENO);
		return (NULL);
	}
	return (var_name);
}

void	track_quotes_until_meta(int *in_dquote, int *in_squote, char *cmd,
		size_t *i)
{
	*in_squote = 0;
	*in_dquote = 0;
	while (cmd[*i] && !ft_isspace(cmd[*i]) && cmd[*i] != '|' && cmd[*i] != '<'
		&& cmd[*i] != '>')
	{
		if (!(*in_dquote) && cmd[*i] == '\'')
			*in_squote = !(*in_squote);
		else if (!(*in_squote) && cmd[*i] == '"')
			*in_dquote = !(*in_dquote);
		(*i)++;
	}
}

int	is_in_single_quotes(const char *cmd, size_t pos)
{
	int		in_squote;
	int		in_dquote;
	size_t	i;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (i < pos && cmd[i])
	{
		if (!in_dquote && cmd[i] == '\'')
			in_squote = !in_squote;
		else if (!in_squote && cmd[i] == '"')
			in_dquote = !in_dquote;
		i++;
	}
	return (in_squote);
}
