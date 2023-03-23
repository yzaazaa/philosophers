#include "philo.h"

int	main(int ac, char **av)
{
	t_wrapper	*wrapper;

	wrapper = (t_wrapper *)malloc(sizeof(t_wrapper));
	if(!wrapper)
		ft_error(ERROR_MALLOC);
	wrapper->args = ft_parser(ac, av);
	return(thread(wrapper));
}