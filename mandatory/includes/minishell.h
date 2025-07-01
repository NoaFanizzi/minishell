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
#include "get_next_line.h"

extern int g_exit_status;
extern int g_macro_debug;

enum	ERROR
{
	O_ERROR = -10,
	NO_IN = -11,
	NO_OUT = -12
};


void	expand(char **command, t_list **var);


#endif