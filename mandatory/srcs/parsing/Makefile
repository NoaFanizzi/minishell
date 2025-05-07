# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 09:44:35 by nbodin            #+#    #+#              #
#    Updated: 2025/05/07 10:13:18 by nbodin           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

FILES = command_to_str \
		quotes_splitting \
		space_splitting \
		meta_splitting \
		quotes_removal \
		command_splitting \
		cmd_struct \
		charset_split \
		test \

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

SRCS_DIR = ./
OBJS_DIR = .obj/
INC_DIR = ../../includes/
#GNL_DIR = $(INC_DIR)get_next_line_1/
LIBFT_DIR = ../../../libft/

HEADER = $(INC_DIR)parsing.h

#GNL = $(GNL_DIR)/get_next_line.a
LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf

NAME = parsing

all: 		$(NAME)

		
$(NAME):	$(OBJS) $(LIBFT) #$(GNL) also put it right below
		$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBFT) -o $@

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c $(HEADER) #-I$(GNL_DIR) put it right below
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -Iusr/include -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@
		
# $(GNL):		FORCE
# 	$(MAKE) --silent -C $(GNL_DIR)

$(LIBFT):	FORCE
	$(MAKE) --silent -C $(LIBFT_DIR)

clean: #$(MAKE) --silent -C $(GNL_DIR) clean    same
		$(RM) $(OBJS_DIR)
		$(MAKE) --silent -C $(LIBFT_DIR) clean

fclean:		clean #$(MAKE) --silent -C $(GNL_DIR) fclean    same
		$(RM) $(NAME)
		$(MAKE) --silent -C $(LIBFT_DIR) fclean
		

re:			fclean all

FORCE: ;

.PHONY:		all clean fclean re FORCE