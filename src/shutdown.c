
#include "minirt.h"

void	error_exit(t_data *d, char *msg)
{
	int		discard;

	free_all(d);
	discard = write(2, msg, ft_strlen(msg));
	(void)discard;
	exit(1);
}

void	free_all(t_data *d)
{
	if (d->parse.fd != -1)
		close(d->parse.fd);
	if (d->parse.elmnts)
		free_2d_char(d->parse.elmnts);
	if (d->parse.subelmnts)
		free_2d_char(d->parse.subelmnts);
	if (d->objectlist)
		objlst_free(d->objectlist);
	if (d->lightlst)
		lightlst_free(d->lightlst);
	if (d->mlx.initialized)
		mlx_destroy_image(d->mlx.mlx, d->mlx.img);
}
