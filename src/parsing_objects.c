# include "../incl/minirt.h"

/*
Sphere:
sp 0.0,0.0,20.6 12.6 10,0,255
∗ identifier: sp (-> elements[0])
∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6 (-> elements[1])
∗ the sphere diameter: 12.6 (-> elements[2])
∗ R,G,B colors in range [0-255]: 10, 0, 255 (-> elements[3])
*/
void	parse_sphere(t_data *d)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_exit(d, E_MALLOC);
	parse_tpoint(d, &sphere->center, 1, E_SPHERE1);
	d->parse.min = 0;
	d->parse.max = 0;
	parse_double(d, &sphere->diameter, 2, E_SPHERE2);
	parse_tcolor(d, &sphere->color, 3, E_SPHERE3);
	objlst_add_back(&d->objectlist, objlst_new(sphere, sp));
}
