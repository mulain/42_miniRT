# include "../incl/minirt.h"

int	main(int argc, char **argv)
{
	t_data		data;

	init_structs(&data);

	parsing(&data, argc, argv);
	init_mlx(&data);
	ite_ray(&data);
	printf("iteray done\n");
	mlx_put_image_to_window(data.mlx.mlx, data.mlx.win,
		data.mlx.img, 0, 0);
	mlx_loop((&data.mlx));

}

void init_structs(t_data *d)
{
	d->amb_light.declared = false;
	d->amb_light.brightness = 0;
	d->amb_light.color = (t_color){0, 0, 0};
	d->camera.declared = false;
	d->camera.fov = 0;
	d->camera.normvector = (t_vector){0, 0, 0};
	d->camera.org = (t_vector){0, 0, 0};
	d->light.declared = false;
	d->light.brightness = 0;
	d->light.color = (t_color){0, 0, 0};
	d->light.coordinates = (t_vector){0, 0, 0};
	d->objectlist = NULL;
}

void	init_mlx(t_data *d)
{
	d->mlx.mlx = mlx_init();
	// d->mlx.win = mlx_new_window(d->mlx.mlx, d->mlx.img_width, d->mlx.img_height, "miniRT");
	d->mlx.win = mlx_new_window(d->mlx.mlx, WIDTH, HEIGHT, "miniRT");
	// d->mlx.img = mlx_new_image(d->mlx.mlx, d->mlx.img_width, d->mlx.img_height);
	d->mlx.img = mlx_new_image(d->mlx.mlx, WIDTH, HEIGHT);
	d->mlx.img_addr = mlx_get_data_addr(d->mlx.img, &d->mlx.img_bpp, &d->mlx.img_line_length,
			&d->mlx.img_endian);
	d->mlx.img_bytespp = d->mlx.img_bpp / 8;


}
