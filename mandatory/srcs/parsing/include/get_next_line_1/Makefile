# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 16:01:18 by nbodin            #+#    #+#              #
#    Updated: 2025/04/01 16:50:47 by nbodin           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

FILES = get_next_line \
		get_next_line_utils

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

SRCS_DIR = 
OBJS_DIR = .obj/
INC_DIR = ./

HEADER = $(INC_DIR)get_next_line.h

CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf
AR = ar rcs
OUT = a.out

NAME = get_next_line.a

all: 		$(NAME)
		
$(NAME):	$(OBJS)
		$(AR) $(NAME) $(OBJS)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c $(HEADER)
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@
		
clean:
		$(RM) $(OBJS_DIR)

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(OUT)

re:			fclean all


.PHONY:		all clean fclean re