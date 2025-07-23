/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 08:20:46 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/23 23:34:30 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	deal_with_sigint(int signal)
{
	//printf("\ndeal_with_sigint called\n");
	g_signal = signal;
	ft_putendl_fd("^C", STDERR_FILENO);
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	deal_with_sigint_hdoc(int signal)
{
	//printf("\ndeal_with_sigint_hdoc called\n");
	g_signal = signal;
	ft_putstr_fd("^C", STDERR_FILENO);
	close(STDIN_FILENO);
	//printf("g_signal = %d\n", 1);
	//dprintf(STDERR_FILENO, "g_signal = %d\n", g_signal);
}

void	deal_with_signals_in_exec(int signal)
{
	//printf("\ndeal_with_signals_in_exec called\n");
	g_signal = signal;
}

void	deal_with_signal_after_exec(void)
{
	if(g_signal == 0)
		return;
	if(g_signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_signal = 0;
}