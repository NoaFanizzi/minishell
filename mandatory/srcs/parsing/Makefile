# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 15:38:30 by nbodin            #+#    #+#              #
#    Updated: 2025/04/16 17:39:30 by nbodin           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

FILES = command_to_str \
		quotes_splitting \
		space_splitting \
		meta_splitting \
		quotes_removal \
		command_splitting \
		charset_split \
		test \

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

SRCS_DIR = src/
OBJS_DIR = .obj/
INC_DIR = include/
GNL_DIR = $(INC_DIR)get_next_line_1/
LIBFT_DIR = ../../../libft/

HEADER = $(INC_DIR)parsing.h

GNL = $(GNL_DIR)/get_next_line.a
LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf

NAME = parsing

all: 		$(NAME)

		
$(NAME):	$(OBJS) $(GNL) $(LIBFT)
		$(CC) $(CFLAGS) -lreadline $(OBJS) $(GNL) $(LIBFT) -o $@

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c $(HEADER)
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -Iusr/include -I$(INC_DIR) -I$(GNL_DIR) -I$(LIBFT_DIR) -c $< -o $@
		
$(GNL):		FORCE
	$(MAKE) --silent -C $(GNL_DIR)

$(LIBFT):	FORCE
	$(MAKE) --silent -C $(LIBFT_DIR)

clean:
		$(RM) $(OBJS_DIR)
		$(MAKE) --silent -C $(GNL_DIR) clean
		$(MAKE) --silent -C $(LIBFT_DIR) clean

fclean:		clean
		$(RM) $(NAME)
		$(MAKE) --silent -C $(GNL_DIR) fclean
		$(MAKE) --silent -C $(LIBFT_DIR) fclean
		

re:			fclean all

FORCE: ;

.PHONY:		all clean fclean re FORCE