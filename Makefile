# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 13:45:35 by nofanizz          #+#    #+#              #
#    Updated: 2025/03/26 11:44:38 by nofanizz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


BINARIES	= minishell

ifeq ($(filter bonus clean fclean,$(MAKECMDGOALS)),)
	include mandatory/mandatory.mk
endif

OBJ_DIR = .obj
DEP_DIR = .dep
LIBFT_DIR = libft

LIBFT		= $(LIBFT_DIR)/libft.a

CC		= cc
C_FLAGS = -g -Wall -Wextra -Werror
D_FLAGS = -MMD -MP -MF $(DEP_DIR)/$*.d
I_FLAGS = -I$(INC_DIR) -I$(LIBFT_DIR)/includes
L_FLAGS = -L$(LIBFT_DIR) -lft
CF		= $(CC) $(C_FLAGS) $(I_FLAGS)

vpath %.c $(LIBFT_DIR)/srcs
vpath %.h $(LIBFT_DIR)/includes
vpath %.o $(OBJ_DIR) $(LIBFT_DIR)/$(OBJ_DIR)
vpath %.d $(DEP_DIR) $(LIBFT_DIR) /$(DEP_DIR)

OBJS	= $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
DEPS	= $(addprefix $(DEP_DIR)/, $(notdir $(SRCS:.c=.d)))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Creating $(NAME)\n"
	@$(CF) $^ $(L_FLAGS) -o $@
	@echo "Program Created \n"

bonus: $(NAME)

$(LIBFT): FORCE
	@echo "Bulding libft \n"
	@$(MAKE) -s -C $(LIBFT_DIR)
	
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR) $(DEP_DIR)
	@echo "Compilation $< $@ "
	@$(CF) $(D_FLAGS) -c $< -o $@

$(OBJ_DIR) $(DEP_DIR):
	@echo "Creating obj directory"
	@mkdir -p $@

clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "Deleting obj files"
	@rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean:
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "Deleting obj files"
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@echo "Removing binaries"
	@rm -f $(BINARIES)

-include $(DEPS)

.PHONY: all clean fclean re debug help
FORCE: