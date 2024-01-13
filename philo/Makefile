#SOURCE FILES
SRCS = srcs/setup.c srcs/loop.c srcs/main.c srcs/parse.c

#OBJECT FILES
OBJS = ${SRCS:.c=.o}

#HEADERS
HEADERS = includes/philo.h

#PROGRAM NAME
NAME = philo

#COMPILER
CC = cc

#FLAGS
CFLAGS = -Wall -Wextra -Werror -pthread

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean :
	rm -rf $(OBJS) $(NAME)

re : fclean all

.PHONY : fclean clean