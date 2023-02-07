# include "../incl/minirt.h"

void	exit_msg(char *msg)
{
	write (2, msg, ft_strlen(msg));
	exit(1);
}
