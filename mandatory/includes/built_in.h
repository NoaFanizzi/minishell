#ifndef BUILT_IN_H
#define BUILT_IN_H

#include "minishell.h"

//cd.c
int		ft_update_pwd(t_list **env);
int		ft_access_dir(t_content *content);
int		ft_update_opwd(t_list **env, t_content *content);
int		ft_find_wave(t_list *env, t_content *content);
int		ft_find_dash(t_list *env, t_content *content);
int		ft_deal_with_dash(t_content *content, t_list **env);
int		ft_deal_with_wave(t_content *content, t_list **env);
void	ft_cd(t_content *content, t_list **env);

//echo.c
int		ft_is_arg(char *cmd);
int		ft_echo(t_content *content);

//env.c
int		ft_get_right_op(t_env *link, char *env, size_t i);
int		ft_get_right_arg(t_env *link, char *env, size_t	i);
t_env	*fill_env_arg(t_env **link, char *env, size_t *var_len);
t_env	*ft_add_new_link(char *env);
t_list	*ft_init_env(char **o_env);
void	ft_display_env(t_list *env, t_content *content);

//exit.c
void	ft_free_hdoc(t_heredocs *hdoc);
void	ft_check_if_valid_exit(t_content *content);
void	ft_exit(t_content *content);

//expand_utils.c
size_t	get_true_var_length(char *var_name, t_list *env);
int		var_exists(char *var_name, t_list *env);
char	*get_var_value(char *var_name, t_list *env);

//export_dup.c
t_env	*dup_env_node(t_env *e);
t_list	*dup_env_list(t_list *env);

//export.c
int		ft_check_if_in_base(t_list *env, char *str);
int		ft_is_a_value(char *str);
int		ft_is_chr(char *str, char c);
int		ft_check_if_first_nod(t_list *first_nod, t_list *previous);
void 	ft_display_export(t_list *env_copy);
int		is_number(char c);
int		ft_check_var_validity(char *var);
int		ft_init_export(t_list **env, t_content *content, size_t	i);
int		ft_export(t_list **env, t_content *content);

//pwd.c
int		ft_pwd(void);

//unset.c
void	ft_free_link(void *content);
void	ft_rm_link(t_list **env, int pos);
void	ft_rm_first_link(t_list **env);
int		ft_init_unset(t_list **env, t_content *content, size_t	i);
int		ft_unset(t_list **env, t_content *content);

#endif