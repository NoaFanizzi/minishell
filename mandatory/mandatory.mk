NAME				= minishell

DIR					= mandatory
SRC_DIR				= $(DIR)/srcs
INC_DIR				= $(DIR)/includes
BUILT_IN_DIR		= built-in
EXEC_DIR			= exec
PARSING_DIR			= parsing


BUILT_IN_SRCS	= echo.c cd.c env.c pwd.c export.c unset.c
BUILT_IN_SRCS	:= $(addprefix $(BUILT_IN_DIR)/, $(BUILT_IN_SRCS))

EXEC_SRCS = exec_cmd.c exec_free.c exec_init.c exec_utils.c exec_env_conversion.c
EXEC_SRCS := $(addprefix $(EXEC_DIR)/, $(EXEC_SRCS))

PARSING_SRCS = command_to_str quotes_splitting space_splitting meta_splitting quotes_removal command_splitting cmd_struct charset_split test
EXEC_SRCS := $(addprefix $(PARSING_DIR)/, $(PARSING_SRCS))

SRCS		= main.c utils.c \
			  $(BUILT_IN_SRCS) $(EXEC_SRCS) $(PARSING_SRCS)
SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS))




vpath %.c $(SRC_DIR) $(SRC_DIR)/$(BUILT_IN_DIR) $(SRC_DIR)/$(EXEC_DIR)
vpath %.h $(INC_DIR)