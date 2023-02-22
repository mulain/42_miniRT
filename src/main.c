
#include "minirt.h"

void	testshit(t_data *d)
{
	double		test;
	t_ray		ray;
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;

	(void)d;
	// ray
	ray.point = (t_vector){0, 0, 0};
	ray.vector = (t_vector){0, 1, 100};
	// sphere
	sphere.point = (t_vector){0, 0, 0};
	sphere.radius = 1;
	test = intersect_sphere(ray, sphere);
	printf("intersect sphere: %f\n", test);
	// plane
	plane.point = (t_vector){0, 1.0, 0};
	plane.vector = (t_vector){0, 1, 0};
	test = intersect_plane(ray, plane);
	printf("intersect plane:%f\n", test);
	cylinder.point = (t_vector){0, 1, 0};
	cylinder.vector = (t_vector){0, 1, 0};
	cylinder.radius = 1;
	cylinder.height = 1;
	test = intersect_cylinder(ray, cylinder);
	printf("intersect cylinder:%f\n", test);
	/*
	// print the input file objects
	print_ambientlight(d);
	print_light(d);
	print_camera(d);
	print_objlist(d->objectlist);
	*/
}

int	main(int argc, char **argv)
{
	t_data		data;

	init_structs(&data);
	get_infile(&data, argc, argv);
	parsing(&data);
	init_mlx(&data);
	testshit(&data);
	mlx_key_hook(data.mlx.win, key_release, &data);
	mlx_hook(data.mlx.win, 17, 0L << 0, event_windowdestroy, &data);
	mlx_loop(data.mlx.mlx);
	free_all(&data);
	return (0);
}

void	get_infile(t_data *d, int argc, char **argv)
{
	int		len;

	if (argc < 2)
		error_exit(d, E_ARGCOUNT);
	len = ft_strlen(argv[1]);
	if (len < 4)
		error_exit(d, E_FILENAME);
	if (ft_strncmp(argv[1] + len - 3, ".rt", 4))
		error_exit(d, E_FILETYPE);
	d->parse.fd = open(argv[1], 0);
	if (d->parse.fd == -1)
		error_exit(d, E_OPENFILE);
}

void	init_structs(t_data *d)
{
	d->width = IMG_WIDTH;
	d->height = IMG_HEIGHT;
	d->aspect_ratio = d->width / d->height;
	d->mlx.initialized = false;
	d->amb_light.declared = false;
	d->amb_light.brightness = 0.0;
	d->amb_light.color = (t_color){0, 0, 0};
	d->camera.declared = false;
	d->camera.fieldofview = 0;
	d->camera.vector = (t_vector){0, 0, 0};
	d->camera.point = (t_vector){0, 0, 0};
	d->light.declared = false;
	d->light.brightness = 0.0;
	d->light.color = (t_color){0, 0, 0};
	d->light.point = (t_vector){0, 0, 0};
	d->objectlist = NULL;
	d->parse.fd = -1;
	d->parse.elmnts = NULL;
	d->parse.subelmnts = NULL;
	d->parse.min = 0.0;
	d->parse.max = 0.0;
}

void	init_mlx(t_data *d)
{
	t_mlx		*m;

	m = &d->mlx;
	m->img_width = d->width;
	m->img_height = d->height;
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, m->img_width, m->img_height, "miniRT");
	m->img = mlx_new_image(m->mlx, m->img_width, m->img_height);
	m->img_addr = mlx_get_data_addr(m->img, &m->img_bpp, &m->img_line_length,
			&m->img_endian);
	m->img_bytespp = m->img_bpp / 8;
	m->initialized = true;
}
