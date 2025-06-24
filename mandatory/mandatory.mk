NAME				= minishell

DIR					= mandatory
SRC_DIR				= $(DIR)/srcs
INC_DIR				= $(DIR)/includes
BUILT_IN_DIR		= built-in
EXEC_DIR			= exec
PARSING_DIR			= parsing
REDIRECTIONS_DIR	= redirections
ERROR_HANDLING_DIR = error_handling


BUILT_IN_SRCS	= echo.c cd.c env.c pwd.c export.c export_dup.c unset.c
BUILT_IN_SRCS	:= $(addprefix $(BUILT_IN_DIR)/, $(BUILT_IN_SRCS))

ERROR_HANDLING_SRCS = error_handling_error_code.c
ERROR_HANDLING_SRCS := $(addprefix $(ERROR_HANDLING_DIR)/, $(ERROR_HANDLING_SRCS))

REDIRECTIONS_SRCS = redirections_infile.c redirections_outfile.c redirections_find.c
REDIRECTIONS_SRCS := $(addprefix $(REDIRECTIONS_DIR)/, $(REDIRECTIONS_SRCS))

EXEC_SRCS = exec_cmd.c exec_free.c exec_init.c exec_utils.c exec_env_conversion.c
EXEC_SRCS := $(addprefix $(EXEC_DIR)/, $(EXEC_SRCS)) $(addprefix $(EXEC_DIR)/, $(REDIRECTIONS_SRCS)) $(addprefix $(EXEC_DIR)/, $(ERROR_HANDLING_SRCS))

PARSING_SRCS = command_to_str.c quotes_splitting.c space_splitting.c meta_splitting.c quotes_removal.c command_splitting.c cmd_struct.c charset_split.c test.c contiguous_quotes.c
PARSING_SRCS := $(addprefix $(PARSING_DIR)/, $(PARSING_SRCS))

SRCS		= main.c utils.c \
			  $(BUILT_IN_SRCS) $(EXEC_SRCS) $(PARSING_SRCS)
SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS))




vpath %.c $(SRC_DIR) $(SRC_DIR)/$(BUILT_IN_DIR) $(SRC_DIR)/$(EXEC_DIR) $(SRC_DIR)/$(PARSING_DIR) $(SRC_DIR)/$(EXEC_DIR)/$(REDIRECTIONS_DIR) $(SRC_DIR)/$(EXEC_DIR)/$(ERROR_HANDLING_DIR)
vpath %.h $(INC_DIR)