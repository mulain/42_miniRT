
#include "../incl/minirt.h"

void	parse_sphere(t_data *d)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_exit(d, E_MALLOC);
	objlst_add_back(&d->objectlist, objlst_new(sphere, sp));
	sphere->center = parse_point(d, d->parse.elmnts[1], E_SPHERE1);
	d->parse.min = 0;
	d->parse.max = 0;
	sphere->radius = 0.5 * parse_double(d, d->parse.elmnts[2], E_SPHERE2);
	sphere->color = parse_color(d, d->parse.elmnts[3], E_SPHERE3);
}

void	parse_plane(t_data *d)
{
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		error_exit(d, E_MALLOC);
	objlst_add_back(&d->objectlist, objlst_new(plane, pl));
	plane->point = parse_point(d, d->parse.elmnts[1], E_PLANE1);
	plane->vector = parse_vector(d, d->parse.elmnts[2], E_PLANE2);
	plane->color = parse_color(d, d->parse.elmnts[3], E_PLANE3);
}

void	parse_cylinder(t_data *d)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		error_exit(d, E_MALLOC);
	objlst_add_back(&d->objectlist, objlst_new(cylinder, cy));
	cylinder->center = parse_point(d, d->parse.elmnts[1], E_CYLINDER1);
	cylinder->axis = parse_vector(d, d->parse.elmnts[2], E_CYLINDER2);
	d->parse.min = 0.0;
	d->parse.max = 0.0;
	cylinder->radius = 0.5 * parse_double(d, d->parse.elmnts[3], E_CYLINDER3);
	cylinder->height = parse_double(d, d->parse.elmnts[4], E_CYLINDER4);
	cylinder->color = parse_color(d, d->parse.elmnts[5], E_CYLINDER5);
}
