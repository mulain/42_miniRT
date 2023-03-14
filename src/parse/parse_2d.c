
#include "../incl/minirt.h"

void	parse_plane(t_data *d)
{
	t_plane		*plane;
	t_objlst	*new;
	t_3d		temp;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		error_exit(d, E_MALLOC);
	new = objlst_new(d, plane, pl);
	objlst_add_back(&d->objectlist, new);
	d->parse.check_range = false;
	plane->point = parse_point(d, d->parse.elmnts[1], E_PLANE1);
	plane->vector = parse_vector(d, d->parse.elmnts[2], E_PLANE2);
	plane->color = parse_color(d, d->parse.elmnts[3], E_PLANE3);
	temp = parse_vector(d, d->parse.elmnts[4], E_PLANEMAT);
	new->phong = (t_phong){temp.x, temp.y, temp.z};
}

void	parse_disc(t_data *d)
{
	t_disc		*disc;
	t_objlst	*new;
	t_3d		temp;

	disc = malloc(sizeof(t_disc));
	if (!disc)
		error_exit(d, E_MALLOC);
	new = objlst_new(d, disc, di);
	objlst_add_back(&d->objectlist, new);
	d->parse.check_range = false;
	disc->center = parse_point(d, d->parse.elmnts[1], E_DISC1);
	disc->vector = parse_vector(d, d->parse.elmnts[2], E_DISC2);
	disc->radius = 0.5 * parse_double(d, d->parse.elmnts[3], E_DISC3);
	disc->color = parse_color(d, d->parse.elmnts[4], E_DISC4);
	temp = parse_vector(d, d->parse.elmnts[5], E_DISCMAT);
	new->phong = (t_phong){temp.x, temp.y, temp.z};
}

void	parse_triangle(t_data *d)
{
	t_triangle	*triangle;
	t_objlst	*new;
	t_3d		temp;

	triangle = malloc(sizeof(t_triangle));
	if (!triangle)
		error_exit(d, E_MALLOC);
	new = objlst_new(d, triangle, tr);
	objlst_add_back(&d->objectlist, new);
	d->parse.check_range = false;
	triangle->v1 = parse_point(d, d->parse.elmnts[1], E_TRIANGLE1);
	triangle->v2 = parse_point(d, d->parse.elmnts[2], E_TRIANGLE2);
	triangle->v3 = parse_point(d, d->parse.elmnts[3], E_TRIANGLE3);
	triangle->vector = cross(subtract(triangle->v1, triangle->v2),
			subtract(triangle->v1, triangle->v3));
	if (length(triangle->vector) < EPSILON)
		error_exit(d, E_TRI_VECTOR);
	triangle->color = parse_color(d, d->parse.elmnts[4], E_TRIANGLE4);
	temp = parse_vector(d, d->parse.elmnts[5], E_TRIANGLEMAT);
	new->phong = (t_phong){temp.x, temp.y, temp.z};
}
