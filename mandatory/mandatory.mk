NAME				= minishell

DIR					= mandatory
SRC_DIR				= $(DIR)/srcs
INC_DIR				= $(DIR)/includes
BUILT_IN_DIR		= built-in


BUILT_IN_SRCS	= echo.c cd.c env.c pwd.c
BUILT_IN_SRCS	:= $(addprefix $(BUILT_IN_DIR)/, $(BUILT_IN_SRCS))



SRCS		= main.c utils.c \
			  $(BUILT_IN_SRCS)
SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS))


vpath %.c $(SRC_DIR) $(SRC_DIR)/$(BUILT_IN_DIR)
vpath %.h $(INC_DIR)