
#include "../incl/minirt.h"

void	error_exit(t_data *d, char *msg)
{
	free_all(d);
	if (d->parse.fd != -1)
		close(d->parse.fd);
	write (2, msg, ft_strlen(msg));
	exit(1);
}

void	free_all(t_data *d)
{
	if (d->parse.elmnts)
		free_2d_char(d->parse.elmnts);
	if (d->parse.subelmnts)
		free_2d_char(d->parse.subelmnts);
	if (d->objectlist)
		objlist_free(d->objectlist);
}
