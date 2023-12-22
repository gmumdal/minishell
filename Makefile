NAME = minishell
SRC_DIR = srcs
SRCS = main.c ms_parsing.c ms_split.c \
	ms_tokennew.c ms_tokenadd_back.c termios.c \
	ms_tokenclear.c ms_expend_edit.c side_utils.c \
	debug.c data_list.c ms_utils1.c \
	pipe.c pipe_utils.c pipe_parse.c heredoc.c \
	builtin_utils.c builtin_cd.c builtin_unset.c \
	error_execute.c signal.c heredoc_expend.c \
	builtin_exit.c builtin_export.c builtin_env.c builtin_echo.c
OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INC_DIR := incs
INCS = minishell.h
LIBFT = -Ilibft -Llibft -lft
READ = -lreadline
LIBFT_DIR = libft
CC = cc
CFLAGS = -Wall -Wextra -Werror
INC_FLAGS = -I $(INC_DIR) -Ilibft

all : $(NAME)

$(NAME) : $(OBJS)
	make -sC $(LIBFT_DIR) all
	$(CC) $(CFLAGS) $(READ) -o $@ $^ $(LIBFT)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INC_FLAGS)

clean :
	make -sC $(LIBFT_DIR) fclean
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
