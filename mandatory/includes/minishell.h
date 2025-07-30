/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:46:58 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/30 10:18:08 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "error_handling.h"
# include "exec.h"
# include "get_next_line.h"
# include "libft.h"
# include "parsing.h"
# include "redirections.h"
# include "structs.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/select.h>
# include <sys/stat.h>
# include <unistd.h>

extern int	g_signal;

enum		e_ERROR
{
	O_ERROR = -10,
	NO_IN = -11,
	NO_OUT = -12
};

int			track_var_in_del(char *cmd, size_t *i, size_t var_index);
void		child_handler(int signal);
void		deal_with_sigint(int signal);
void		deal_with_sigint_hdoc(int signal);
void		deal_with_signals_in_exec(int signal);
void		deal_with_signal_after_exec(void);

#endif