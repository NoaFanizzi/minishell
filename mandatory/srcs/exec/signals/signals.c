/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 08:20:46 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/28 22:06:10 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_handler(int signal)
{
	(void)signal;
	g_signal = 1;
}

void	deal_with_sigint(int signal)
{
	g_signal = signal;
	ft_putendl_fd("^C", STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	deal_with_sigint_hdoc(int signal)
{
	g_signal = signal;
	ft_putstr_fd("^C", STDERR_FILENO);
	close(STDIN_FILENO);
}

void	deal_with_signals_in_exec(int signal)
{
	g_signal = signal;
}

void	deal_with_signal_after_exec(void)
{
	signal(SIGINT, deal_with_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (g_signal == 0)
		return ;
	if (g_signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_signal = 0;
}
