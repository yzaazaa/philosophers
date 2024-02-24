SRCS = check_args.c ft_exit.c ft_print.c get_time.c init_data.c main.c manage_philos.c routine.c

OBJS = $(SRCS:.c=.o)

HEADER = philo.h

NAME = philo

CFLAGS = -Wall -Wextra -Werror

COMP = cc

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "Compiling philo ..."
	@$(COMP) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c $(HEADER)
	@echo "Compiling $< ..."
	@$(COMP) $(CFLAGS) -c $< -o $@

clean :
	@echo "Deleting object files ..."
	@rm -rf $(OBJS)

fclean :
	@echo "Deleting all ..."
	@rm -rf $(OBJS) $(NAME)

re : fclean all

.PHONY : clean fclean