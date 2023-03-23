NAME = philo

SRCS = error.c parser.c fork.c philo.c logs.c handler.c main.c

OBJS = ${SRCS:.c=.o}

COMP = gcc

CFLAGS = -Wall -Wextra -Werror

$(NAME):
	$(COMP) $(CFLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all