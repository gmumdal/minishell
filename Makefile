NAME = minishell
SRCS = main.c ms_pasing.c ms_split.c \
debug.c data_list.c ms_utils1.c \
pipe.c pipe_utils.c pipe_parse.c pipe_exit.c heredoc.c
INCS = minishell.h
LIBFT = -Ilibft -Llibft -lft
READ = -lreadline
LIBFT_DIR = libft
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

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
