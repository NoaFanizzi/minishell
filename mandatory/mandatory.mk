NAME				= minishell

DIR					= mandatory
SRC_DIR				= $(DIR)/srcs
INC_DIR				= $(DIR)/includes
BUILT_IN_DIR		= built-in
EXEC_DIR			= exec
PARSING_DIR			= parsing
REDIRECTIONS_DIR	= redirections
ERROR_HANDLING_DIR  = error_handling
GNL_DIR				= GNL
CHILDREN_DIR		= children
PARENTS_DIR			= parents
PIPES_DIR			= pipes
UTILS_DIR			= utils

GNL_SRCS			= get_next_line.c get_next_line_utils.c
GNL_SRCS			:= $(addprefix $(GNL_DIR)/, $(GNL_SRCS))

BUILT_IN_SRCS		= echo.c cd.c env.c pwd.c export.c export_dup.c unset.c exit.c expand_utils.c
BUILT_IN_SRCS		:= $(addprefix $(BUILT_IN_DIR)/, $(BUILT_IN_SRCS))

CHILDREN_SRCS		= children_built_in_dealing.c children_command.c children_process.c
CHILDREN_SRCS		:= $(addprefix $(CHILDREN_DIR)/, $(CHILDREN_SRCS))

PARENTS_SRCS		= parents_built_in_dealing.c parents_get_redirections.c parents_process.c
PARENTS_SRCS		:= $(addprefix $(PARENTS_DIR)/, $(PARENTS_SRCS))

PIPES_SRCS			= pipes_dealing.c
PIPES_SRCS			:= $(addprefix $(PIPES_DIR)/, $(PIPES_SRCS))

REDIRECTIONS_SRCS 	= deal_with_redirections.c redirections_find.c
REDIRECTIONS_SRCS 	:= $(addprefix $(REDIRECTIONS_DIR)/, $(REDIRECTIONS_SRCS))

ERROR_HANDLING_SRCS	= error_handling_error_code.c
ERROR_HANDLING_SRCS	:= $(addprefix $(ERROR_HANDLING_DIR)/, $(ERROR_HANDLING_SRCS))

UTILS_SRCS			= exec_env_conversion.c exec_free.c exec_utils.c
UTILS_SRCS			:= $(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))

# Ici, comme REDIRECTIONS_SRCS a déjà le préfixe redirections/, on ne remet pas exec/ devant :
EXEC_SRCS = $(REDIRECTIONS_SRCS) $(ERROR_HANDLING_SRCS) $(CHILDREN_SRCS) $(PARENTS_SRCS) $(UTILS_SRCS) $(PIPES_SRCS)

PARSING_SRCS = command_to_str.c quotes_splitting.c space_splitting.c meta_splitting.c quotes_removal.c command_splitting.c cmd_struct.c charset_split.c test.c contiguous_quotes.c expand.c
PARSING_SRCS := $(addprefix $(PARSING_DIR)/, $(PARSING_SRCS))

SRCS		= main.c utils.c \
			  $(BUILT_IN_SRCS) $(EXEC_SRCS) $(PARSING_SRCS) $(GNL_SRCS)
SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS))

vpath %.c $(SRC_DIR) $(SRC_DIR)/$(BUILT_IN_DIR) $(SRC_DIR)/$(EXEC_DIR) $(SRC_DIR)/$(PARSING_DIR) \
	$(SRC_DIR)/$(EXEC_DIR)/$(REDIRECTIONS_DIR) $(SRC_DIR)/$(EXEC_DIR)/$(ERROR_HANDLING_DIR) $(SRC_DIR)/$(GNL_DIR) \
	$(SRC_DIR)/$(EXEC_DIR)/$(CHILDREN_DIR) $(SRC_DIR)/$(EXEC_DIR)/$(PARENTS_DIR) $(SRC_DIR)/$(EXEC_DIR)/$(PIPES_DIR) $(SRC_DIR)/$(EXEC_DIR)/$(UTILS_DIR)

vpath %.h $(INC_DIR)