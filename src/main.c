
#include "../incl/minirt.h"

void	testshit(t_data *d)
{
	double		test;
	t_ray		ray;
	t_plane		plane;
	t_sphere	sphere;

	(void)d;
	
	// ray
	ray.point = (t_point){0, 0, 0};
	ray.vector = (t_vector){0, 0, 1};
	
	// sphere
	sphere.point = (t_point){0, 0, 0};
	sphere.radius = 1;
	test = intersect_sphere(ray, sphere);
	printf("intersect sphere: %f\n", test);

	
	// plane
	plane.point = (t_point){0, 1.0, 0};
	plane.vector = (t_vector){0, 1, 0};
	test = intersect_plane(ray, plane);
	printf("intersect plane:%f\n", test);
	
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
	free_all(&data);
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
	d->amb_light.declared = false;
	d->amb_light.brightness = 0.0;
	d->amb_light.color = (t_color){0, 0, 0};
	d->camera.declared = false;
	d->camera.fieldofview = 0;
	d->camera.vector = (t_vector){0, 0, 0};
	d->camera.point = (t_point){0, 0, 0};
	d->light.declared = false;
	d->light.brightness = 0.0;
	d->light.color = (t_color){0, 0, 0};
	d->light.point = (t_point){0, 0, 0};
	d->objectlist = NULL;
	d->parse.fd = -1;
	d->parse.elmnts = NULL;
	d->parse.subelmnts = NULL;
	d->parse.min = 0.0;
	d->parse.max = 0.0;
}

void	init_mlx(t_data *d)
{
	d->mlx.mlx = mlx_init();
	d->mlx.win = mlx_new_window(d->mlx.mlx, d->mlx.img_width, d->mlx.img_height, "miniRT");
	d->mlx.img = mlx_new_image(d->mlx.mlx, d->mlx.img_width, d->mlx.img_height);
	d->mlx.img_addr = mlx_get_data_addr(d->mlx.img, &d->mlx.img_bpp, &d->mlx.img_line_length,
			&d->mlx.img_endian);
	d->mlx.img_bytespp = d->mlx.img_bpp / 8;
}
