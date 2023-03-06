
#include "../incl/minirt.h"

void	parse_plane(t_data *d)
{
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		error_exit(d, E_MALLOC);
	objlst_add_back(&d->objectlist, objlst_new(d, plane, pl));
	plane->point = parse_point(d, d->parse.elmnts[1], E_PLANE1);
	plane->vector = parse_vector(d, d->parse.elmnts[2], E_PLANE2);
	plane->color = parse_color(d, d->parse.elmnts[3], E_PLANE3);
}

void	parse_triangle(t_data *d)
{
	t_triangle	*triangle;

	triangle = malloc(sizeof(t_triangle));
	if (!triangle)
		error_exit(d, E_MALLOC);
	objlst_add_back(&d->objectlist, objlst_new(d, triangle, tr));
	triangle->p1 = parse_point(d, d->parse.elmnts[1], E_TRIANGLE1);
	triangle->p2 = parse_point(d, d->parse.elmnts[2], E_TRIANGLE2);
	triangle->p3 = parse_point(d, d->parse.elmnts[3], E_TRIANGLE3);
	triangle->vector = 
		cross(subtract(triangle->p1, triangle->p2), subtract(triangle->p1, triangle->p3));
	if (length(triangle->vector) < EPSILON)
		error_exit(d, E_TRI_VECTOR);
	triangle->color = parse_color(d, d->parse.elmnts[4], E_TRIANGLE4);
}

void	parse_sphere(t_data *d)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_exit(d, E_MALLOC);
	objlst_add_back(&d->objectlist, objlst_new(d, sphere, sp));
	sphere->center = parse_point(d, d->parse.elmnts[1], E_SPHERE1);
	d->parse.min = 0;
	d->parse.max = 0;
	sphere->radius = 0.5 * parse_double(d, d->parse.elmnts[2], E_SPHERE2);
	sphere->color = parse_color(d, d->parse.elmnts[3], E_SPHERE3);
}

void	parse_cylinder(t_data *d)
{
	t_tube	*tube;
	t_disc	*disc_top;
	t_disc	*disc_base;

	tube = malloc(sizeof(t_tube));
	disc_top = malloc(sizeof(t_disc));
	disc_base = malloc(sizeof(t_disc));
	if (!tube || !disc_top || !disc_base)
		error_exit(d, E_MALLOC);
	objlst_add_back(&d->objectlist, objlst_new(d, tube, tu));
	objlst_add_back(&d->objectlist, objlst_new(d, disc_top, di));
	objlst_add_back(&d->objectlist, objlst_new(d, disc_base, di));
	tube->base = parse_point(d, d->parse.elmnts[1], E_CYLINDER1);
	tube->axis = parse_vector(d, d->parse.elmnts[2], E_CYLINDER2);
	d->parse.min = 0.0;
	d->parse.max = 0.0;
	tube->radius = 0.5 * parse_double(d, d->parse.elmnts[3], E_CYLINDER3);
	tube->height = parse_double(d, d->parse.elmnts[4], E_CYLINDER4);
	tube->top = add(tube->base, mult(tube->axis, tube->height));
	tube->color = parse_color(d, d->parse.elmnts[5], E_CYLINDER5);
	*disc_top = (t_disc){tube->top, tube->axis, tube->radius, tube->color};
	*disc_base = (t_disc){tube->base, tube->axis, tube->radius, tube->color};
}

/* void	parse_cylinder_old(t_data *d)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		error_exit(d, E_MALLOC);
	objlst_add_back(&d->objectlist, objlst_new(d, cylinder, cy));
	cylinder->base = parse_point(d, d->parse.elmnts[1], E_CYLINDER1);
	cylinder->axis = parse_vector(d, d->parse.elmnts[2], E_CYLINDER2);
	d->parse.min = 0.0;
	d->parse.max = 0.0;
	cylinder->radius = 0.5 * parse_double(d, d->parse.elmnts[3], E_CYLINDER3);
	cylinder->height = parse_double(d, d->parse.elmnts[4], E_CYLINDER4);
	cylinder->top = add(cylinder->base, mult(cylinder->axis, cylinder->height));
	cylinder->color = parse_color(d, d->parse.elmnts[5], E_CYLINDER5);
} */
