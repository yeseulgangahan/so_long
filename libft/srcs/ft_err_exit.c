#include "../include/libft.h"

void	ft_err_exit(char *s)
{
	ft_putendl_fd(s, 2);
	exit(EXIT_FAILURE);
}
