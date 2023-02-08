# include "../incl/minirt.h"

int	main(int argc, char **argv)
{
	t_data		data;

	parsing(&data, argc, argv);
	init_mlx(&data);
}

void	init_mlx(t_data *d)
{
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, d->img_width, d->img_height, "miniRT");
	d->img = mlx_new_image(d->mlx, d->img_width, d->img_height);
	d->img_addr = mlx_get_data_addr(d->img, &d->img_bpp, &d->img_line_length,
			&d->img_endian);
	d->img_bytespp = d->img_bpp / 8;
}
