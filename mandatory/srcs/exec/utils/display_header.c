/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:17:30 by nofanizz          #+#    #+#             */
/*   Updated: 2025/07/30 10:50:54 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_top(void)
{
	const char	*line1 = "███╗   ███╗  █████╗  ██╗   ██╗ ██╗ ███";
	const char	*line2 = "███╗  ██   ██╗███████╗ ██       ██      \n";
	const char	*line3 = "████╗ ████║ ██╔══██╗  ╚██ ██╔╝ ██║██╔════╝  ";
	const char	*line4 = "██   ██║██╔════╝ ██       ██      \n";

	write(1, "\n", 1);
	write(1, "\033[1;35m", 7);
	write(1, line1, ft_strlen(line1));
	write(1, line2, ft_strlen(line2));
	write(1, line3, ft_strlen(line3));
	write(1, line4, ft_strlen(line4));
}

void	display_middle(void)
{
	const char	*line1 = "██╔████╔██║ ███████║    ███╔╝  ██║███████";
	const char	*line2 = "╗  ███████║█████╗   ██       ██      \n";
	const char	*line3 = "██║╚██╔╝██║ ██╔══██║   ██╔██╗  ██║╚════██║  ";
	const char	*line4 = "██   ██║██╔══╝   ██       ██      \n";

	write(1, line1, ft_strlen(line1));
	write(1, line2, ft_strlen(line2));
	write(1, line3, ft_strlen(line3));
	write(1, line4, ft_strlen(line4));
}

void	display_bottom(void)
{
	const char	*line1 = "██║ ╚═╝ ██║ ██║  ██║ ██╔╝ ╚██╗ ██║███████║  ";
	const char	*line2 = "██   ██║███████╗ ███████╗ ███████╗\n";
	const char	*line3 = "╚═╝     ╚═╝ ╚═╝  ╚═╝ ╚═╝   ╚═╝ ╚═╝╚══════╝ ";
	const char	*line4 = " ╚═╝  ╚═╝╚══════╝ ╚══════╝ ╚══════╝\n";
	const char	*footer = "                     by nbodin and nofanizz\n";

	write(1, line1, ft_strlen(line1));
	write(1, line2, ft_strlen(line2));
	write(1, line3, ft_strlen(line3));
	write(1, line4, ft_strlen(line4));
	write(1, footer, ft_strlen(footer));
	write(1, "\033[0m\n", 5);
}

void	display_header(void)
{
	display_top();
	display_middle();
	display_bottom();
}
