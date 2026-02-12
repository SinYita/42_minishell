NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS =$(wildcard *.c)

OBJS = $(SRCS:.c=.o)

$(NAME):$(OBJS)
	ar rcs 	$(NAME) $(OBJS)
clean:
	rm -f $(OBJS)
fclean:clean
	rm -f $(NAME)
all:$(NAME)
re:fclean all
.PHONY:
	all clean fclean re


