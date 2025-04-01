# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 15:38:30 by nbodin            #+#    #+#              #
#    Updated: 2025/04/01 17:11:49 by nbodin           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

FILES = command_to_str

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

SRCS_DIR = src/
OBJS_DIR = .obj/
INC_DIR = include/
GNL_DIR = $(INC_DIR)get_next_line_1/

HEADER = $(INC_DIR)parsing.h

GNL = $(GNL_DIR)/get_next_line.a

CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf

NAME = parsing

all: 		$(NAME)

		
$(NAME):	$(OBJS) $(GNL)
		$(CC) $(CFLAGS) $(OBJS) $(GNL) -o $@

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c $(HEADER)
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -Iusr/include -I$(INC_DIR) -I$(GNL_DIR) -c $< -o $@
		
$(GNL):		FORCE
	$(MAKE) --silent -C $(GNL_DIR)

clean:
		$(RM) $(OBJS_DIR)
		$(MAKE) --silent -C $(GNL_DIR) clean

fclean:		clean
		$(RM) $(NAME)
		$(MAKE) --silent -C $(GNL_DIR) fclean

re:			fclean all

FORCE: ;

.PHONY:		all clean fclean re FORCE