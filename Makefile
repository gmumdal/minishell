NAME = minishell
SRCS = main.c ms_parsing.c ms_split.c \
	ms_tokennew.c ms_tokenadd_back.c \
	ms_tokenclear.c ms_expend_edit.c side_utils.c \
	ms_utils1.c
INCS = minishell.h
LIBFT = -Ilibft -Llibft -lft
READ = -lreadline
LIBFT_DIR = libft
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

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
