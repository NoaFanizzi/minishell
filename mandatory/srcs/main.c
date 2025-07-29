/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:05:10 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/29 08:29:21 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0;

void display_header(void)
{
    write(1, "\n", 1);
    write(1, "\033[1;35m", 7);
    
    const char *line1 = "███╗   ███╗  █████╗  ██╗   ██╗ ██╗ ██████╗  ██   ██╗███████╗ ██       ██      \n";
    const char *line2 = "████╗ ████║ ██╔══██╗  ╚██ ██╔╝ ██║██╔════╝  ██   ██║██╔════╝ ██       ██      \n";
    const char *line3 = "██╔████╔██║ ███████║    ███╔╝  ██║███████╗  ███████║█████╗   ██       ██      \n";
    const char *line4 = "██║╚██╔╝██║ ██╔══██║   ██╔██╗  ██║╚════██║  ██   ██║██╔══╝   ██       ██      \n";
    const char *line5 = "██║ ╚═╝ ██║ ██║  ██║ ██╔╝ ╚██╗ ██║███████║  ██   ██║███████╗ ███████╗ ███████╗\n";
    const char *line6 = "╚═╝     ╚═╝ ╚═╝  ╚═╝ ╚═╝   ╚═╝ ╚═╝╚══════╝  ╚═╝  ╚═╝╚══════╝ ╚══════╝ ╚══════╝\n";

    const char *footer = "                     by nbodin and nofanizz\n";

    write(1, line1, strlen(line1));
    write(1, line2, strlen(line2));
    write(1, line3, strlen(line3));
    write(1, line4, strlen(line4));
    write(1, line5, strlen(line5));
    write(1, line6, strlen(line6));
    write(1, footer, strlen(footer));

    write(1, "\033[0m\n", 5);
}

int	main(int argc, char **argv, char **env)
{
	t_list *var;
	int returned_value;
	t_array	array;
	
	(void)argc;
	(void)argv;

    var = NULL;
	array.p_exit_status = 0;
	if(argc != 1)
		return(0);
	if (!isatty(STDOUT) || !isatty(STDIN))
	{
		printf("minishell: not a tty\n");
		exit(1);
	}
	var = ft_init_env(env, &array);
	display_header();
	returned_value = launch_shell(&var, &array);
	ft_free_env(var);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(returned_value);
}
