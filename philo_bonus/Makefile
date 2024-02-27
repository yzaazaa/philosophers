SRCS = check_args.c ft_exit.c ft_print.c ft_time.c init_data.c main.c process.c watch_death.c setter_getter.c 

OBJS = $(SRCS:.c=.o)

HEADER = philo_bonus.h

NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror -g

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