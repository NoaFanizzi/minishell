#ifndef REDIRECTIONS_H
#define REDIRECTIONS_H

#include "minishell.h"

//redirections_find.c
int		ft_parse_redirections(t_content *content, t_expar *expar);
void	ft_get_right_release(t_content *content, t_expar *expar, int type, int channel);

//redirections_infile.c
int	ft_get_infile(t_content *content);

//redirections_outfile.c
int	ft_get_outfile(t_content *content);



#endif