#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "structs.h"
#include "exec.h"
#include "parsing.h"
#include "redirections.h"
#include "error_handling.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "get_next_line.h"
#include <sys/stat.h>

extern int g_signal;

enum	ERROR
{
	O_ERROR = -10,
	NO_IN = -11,
	NO_OUT = -12
};


void	deal_with_sigint(int signal);
void	deal_with_sigint_hdoc(int signal);


#endif