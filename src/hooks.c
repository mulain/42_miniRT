
#include "minirt.h"

int	key_release(int key, t_data *d)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(d->mlx.mlx, d->mlx.win);
		free_all(d);
		exit(0);
	}
	return (1);
}

int	event_windowdestroy(t_data *d)
{
	free_all(d);
	exit(0);
}
