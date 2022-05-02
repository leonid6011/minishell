CC = gcc
SRCS = minishell.c help.c
NAME = minishell
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
%.o:%.c *.h
	$(CC) $(CFLAGS) -c $< -o $@
all		: *.h
	@$(MAKE) $(NAME)
$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline
clean	:
	rm -rf *.o
fclean	: clean
	rm -rf $(NAME)
re: fclean all

.PHONY	: all clean fclean re