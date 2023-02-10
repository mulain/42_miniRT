# include "../incl/minirt.h"

void	exit_onlymsg(char *msg)
{
	write (2, msg, ft_strlen(msg));
	exit(1);
}

void exit_free(char *msg)
{
	//freefunction
	exit_onlymsg(msg);
}
