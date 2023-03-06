
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

void	parse_disc(t_data *d)
{
	t_disc		*disc;

	disc = malloc(sizeof(t_disc));
	if (!disc)
		error_exit(d, E_MALLOC);
	disc->center = parse_point(d, d->parse.elmnts[1], E_DISC1);
	disc->vector = parse_vector(d, d->parse.elmnts[2], E_DISC2);
	d->parse.min = 0;
	d->parse.max = 0;
	disc->radius = 0.5 * parse_double(d, d->parse.elmnts[3], E_DISC3);
	disc->color = parse_color(d, d->parse.elmnts[4], E_DISC4);
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
