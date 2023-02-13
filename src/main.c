# include "../incl/minirt.h"

int	main(int argc, char **argv)
{
	t_data		data;
	int			fd;

	fd = get_infile(&data, argc, argv);
	init_structs(&data);
	parsing(&data, fd);
	//init_mlx(&data);
	free_all(&data);
}

int	get_infile(t_data *d, int argc, char **argv)
{
	int		fd;
	int		len;

	if (argc < 2)
		error_exit(d, E_ARGCOUNT);
	len = ft_strlen(argv[1]);
	if (len < 4)
		error_exit(d, E_FILENAME);
	if (ft_strncmp(argv[1] + len - 3, ".rt", 4))
		error_exit(d, E_FILETYPE);
	fd = open(argv[1], 0);
	if (fd == -1)
		error_exit(d, E_OPENFILE);
	return (fd);
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