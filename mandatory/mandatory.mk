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
SIGNALS_DIR			= signals

GNL_SRCS			= get_next_line.c get_next_line_utils.c
GNL_SRCS			:= $(addprefix $(GNL_DIR)/, $(GNL_SRCS))

BUILT_IN_SRCS		= echo.c cd.c cd_dash.c cd_utils.c env.c pwd.c export.c export_dup.c expand_utils.c export_display.c unset.c exit.c 
BUILT_IN_SRCS		:= $(addprefix $(BUILT_IN_DIR)/, $(BUILT_IN_SRCS))

CHILDREN_SRCS		= children_built_in_dealing.c children_command.c children_process.c
CHILDREN_SRCS		:= $(addprefix $(CHILDREN_DIR)/, $(CHILDREN_SRCS))

PARENTS_SRCS		= parents_built_in_dealing.c parents_get_redirections.c parents_process.c
PARENTS_SRCS		:= $(addprefix $(PARENTS_DIR)/, $(PARENTS_SRCS))

PIPES_SRCS			= pipes_dealing.c
PIPES_SRCS			:= $(addprefix $(PIPES_DIR)/, $(PIPES_SRCS))

REDIRECTIONS_SRCS 	= deal_with_redirections.c redirections_find.c here_doc_parents.c here_doc_child.c here_doc_signals.c in.c out.c temp_file_generation.c check_directory.c
REDIRECTIONS_SRCS 	:= $(addprefix $(REDIRECTIONS_DIR)/, $(REDIRECTIONS_SRCS))

ERROR_HANDLING_SRCS	= error_handling_error_code.c
ERROR_HANDLING_SRCS	:= $(addprefix $(ERROR_HANDLING_DIR)/, $(ERROR_HANDLING_SRCS))

UTILS_SRCS			= exec_env_conversion.c exec_free.c exec_utils.c exec_utils_2.c exec_utils_3.c exec_utils_free.c //display_header.c
UTILS_SRCS			:= $(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))

SIGNALS_SRCS		= signals.c
SIGNALS_SRCS		:= $(addprefix $(SIGNALS_DIR)/, $(SIGNALS_SRCS))

# Ici, comme REDIRECTIONS_SRCS a déjà le préfixe redirections/, on ne remet pas exec/ devant :
EXEC_SRCS = $(REDIRECTIONS_SRCS) $(ERROR_HANDLING_SRCS) $(CHILDREN_SRCS) $(PARENTS_SRCS) $(UTILS_SRCS) $(PIPES_SRCS) $(SIGNALS_SRCS)

PARSING_SRCS = launch_shell.c analyse_command.c quotes_splitting.c quotes_splitting_utils.c space_splitting.c \
               meta_splitting.c meta_splitting_utils.c quotes_removal.c command_splitting.c command_splitting_utils.c \
			   cmd_struct.c figure_files.c figure_arg.c figure_cmd_opt.c cmd_struct_utils.c charset_split.c \
			   contiguous_quotes.c contiguous_quotes_utils.c contiguous_quotes_helpers.c join_prev_simple.c join_next_simple.c \
			   join_prev_quotes.c join_next_quotes.c expand.c expand_util.c expand_other_utils.c expand_helpers.c expand_after.c \
			   parse_command.c check_syntax.c check_syntax_utils.c hdoc.c figure_files.c expand_quotes.c contiguous_quote_merging.c
PARSING_SRCS := $(addprefix $(PARSING_DIR)/, $(PARSING_SRCS))

SRCS		= main.c utils.c \
			  $(BUILT_IN_SRCS) $(EXEC_SRCS) $(PARSING_SRCS) $(GNL_SRCS)
SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS))

vpath %.c $(SRC_DIR) $(SRC_DIR)/$(BUILT_IN_DIR) $(SRC_DIR)/$(EXEC_DIR) $(SRC_DIR)/$(PARSING_DIR) \
	$(SRC_DIR)/$(EXEC_DIR)/$(REDIRECTIONS_DIR) $(SRC_DIR)/$(EXEC_DIR)/$(ERROR_HANDLING_DIR) $(SRC_DIR)/$(GNL_DIR) \
	$(SRC_DIR)/$(EXEC_DIR)/$(CHILDREN_DIR) $(SRC_DIR)/$(EXEC_DIR)/$(PARENTS_DIR) $(SRC_DIR)/$(EXEC_DIR)/$(PIPES_DIR) $(SRC_DIR)/$(EXEC_DIR)/$(UTILS_DIR) $(SRC_DIR)/$(EXEC_DIR)/$(SIGNALS_DIR)

vpath %.h $(INC_DIR)