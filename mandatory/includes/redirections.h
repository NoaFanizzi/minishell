#ifndef REDIRECTIONS_H
#define REDIRECTIONS_H

#include "minishell.h"

char *ft_get_temp_file(void);

//--------------------------here_doc.c---------------------------------
int loop_hdoc(t_array *array, size_t size, size_t i);
int	ft_process_here_doc(t_array *array);

#endif