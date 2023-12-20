NAME = minishell
SRCS = main.c ms_parsing.c ms_split.c \
	ms_tokennew.c ms_tokenadd_back.c termios.c \
	ms_tokenclear.c ms_expend_edit.c side_utils.c \
	debug.c data_list.c ms_utils1.c \
	pipe.c pipe_utils.c pipe_parse.c pipe_exit.c heredoc.c \
	builtin_utils.c builtin_cd.c builtin_unset.c \
	error_execute.c \
	signal.c heredoc_expend.c \
	builtin_exit.c builtin_echo.c
INCS = minishell.h
LIBFT = -Ilibft -Llibft -lft
READ = -lreadline
LIBFT_DIR = libft
CC = cc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRCS) $(INCS)
	make -sC $(LIBFT_DIR) all
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(LIBFT) $(READ)

clean :
	make -sC $(LIBFT_DIR) fclean

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
