# include "../incl/minirt.h"

int	main(int argc, char **argv)
{
	t_data		data;

	init_structs(&data);
	parsing(&data, argc, argv);
	//init_mlx(&data);
}

void	init_structs(t_data *d)
{
	d->amb_light.declared = false;
	d->amb_light.brightness = 0;
	d->amb_light.color = (t_color){0, 0, 0};
	d->camera.declared = false;
	d->camera.fieldofview = 0;
	d->camera.normvector = (t_normvector){0, 0, 0};
	d->camera.viewpoint = (t_point){0, 0, 0};
	d->light.declared = false;
	d->light.brightness = 0;
	d->light.color = (t_color){0, 0, 0};
	d->light.coordinates = (t_point){0, 0, 0};
	d->objectlist = NULL;
	d->parse.input = NULL;
	d->parse.elmnts = NULL;
	d->parse.subelmnts = NULL;
	d->parse.min = 0.0;
	d->parse.max = 0.0;
}

/* void	init_mlx(t_data *d)
{
	d->mlx.mlx = mlx_init();
	d->mlx.win = mlx_new_window(d->mlx.mlx, d->mlx.img_width, d->mlx.img_height, "miniRT");
	d->mlx.img = mlx_new_image(d->mlx.mlx, d->mlx.img_width, d->mlx.img_height);
	d->mlx.img_addr = mlx_get_data_addr(d->mlx.img, &d->mlx.img_bpp, &d->mlx.img_line_length,
			&d->mlx.img_endian);
	d->mlx.img_bytespp = d->mlx.img_bpp / 8;
}
 */