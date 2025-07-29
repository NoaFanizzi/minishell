#ifndef REDIRECTIONS_H
#define REDIRECTIONS_H

#include "minishell.h"

int	ft_get_temp_file(char ** random_file, t_content *content);

//--------------------------here_doc.c---------------------------------
int loop_hdoc(t_array *array, size_t size, size_t i);
int	ft_process_here_doc(t_array *array);

#endif