/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:49:35 by nofanizz          #+#    #+#             */
/*   Updated: 2025/08/07 20:05:36 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

int	ft_get_temp_file(char **random_file, t_content *content);

//--------------------------here_doc.c---------------------------------
int	loop_hdoc(t_array *array, size_t size, size_t i);
int	ft_process_here_doc(t_array *array);

#endif