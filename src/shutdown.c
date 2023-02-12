# include "../incl/minirt.h"

void	shutdown(t_data *d)
{
	if (d->objectlist)
		objlist_free(d->objectlist);
}
