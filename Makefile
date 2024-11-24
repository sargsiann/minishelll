NAME = minishell

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = libs
GNL_DIR = $(LIB_DIR)/gnl
LIBFT_DIR = $(LIB_DIR)/libft

# Dependencies
DEPS = Makefile includes/minishell.h includes/prompt.h

# Source Files
SRC_FILES = main.c \
	    $(addprefix utils/, \
	     ft_error.c \
		 utils.c \
	    ) \
	    $(addprefix prompt/, \
	    prompt.c prompt_utils.c signal.c \
	    ) \
	    $(addprefix tokenization/, \
	    tokenization.c token_utils.c identifiers.c \
	    get_word.c get_operator.c \
	    ) \
	    $(addprefix validation/, \
	    validate_by_order.c validate_var_name.c \
	    ) \
	    $(addprefix expansion/, \
	    expansion.c exp_utils.c remover.c \
	    replace.c wildcart.c expand_var.c finder.c wildcart_utils.c\
	    ) \
	    $(addprefix libs/gnl/, \
	    get_next_line.c get_next_line_utils.c \
	    ) \
		$(addprefix parser/, \
		parser.c cases.c parser_utils.c get_comand_info.c get_comand_path.c  free_tree.c\
		) \
		$(addprefix execution/, \
		execution.c get_here_doc.c command_exec.c builtins.c\
		)
# Directories to create for object files
OBJ_SUBDIRS = $(addprefix $(OBJ_DIR)/, \
	utils prompt tokenization validation expansion parser libs/gnl execution)

# Object Files
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Compiler settings
CC = cc
CFLAGS = -Ilibs/readline -Ilibs/libft -Wall -Wextra -Werror
INC = -I libs/libft
LIBFT_LIB = libs/libft/libft.a

# Clean
RM = rm -f

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_SUBDIRS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/libs/gnl/%.o: libs/gnl/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_LIB) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -lreadline -o $(NAME)

$(LIBFT_LIB):
	make -C libs/libft all
	make -C libs/libft bonus

clean:
	$(RM) -r $(OBJ_DIR)
	make -C libs/libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libs/libft fclean

re: fclean all

.PHONY: all clean fclean re
