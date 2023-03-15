
#include "../incl/minirt.h"

void	parse_plane(t_data *d)
{
	t_plane		*plane;
	t_objlst	*new;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		error_exit(d, E_MALLOC);
	new = objlst_new(d, plane, pl);
	objlst_add_back(&d->objectlist, new);
	d->parse.check_range = false;
	plane->point = parse_point(d, d->parse.elmnts[1], E_PLANE1);
	plane->vector = parse_vector(d, d->parse.elmnts[2], E_PLANE2);
	plane->color = parse_color(d, d->parse.elmnts[3], E_PLANE3);
	new->phong = parse_phong(d, d->parse.elmnts[4], E_PLANEMAT);
	set_range(d, 2.0, 1200);
	new->spec_exp = parse_int(d, d->parse.elmnts[5], E_PLANEEXP);
}

void	parse_disc(t_data *d)
{
	t_disc		*disc;
	t_objlst	*new;

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
	new->phong = parse_phong(d, d->parse.elmnts[5], E_DISCMAT);
	set_range(d, 2.0, 1200);
	new->spec_exp = parse_int(d, d->parse.elmnts[6], E_DISCEXP);
}

void	parse_triangle(t_data *d)
{
	t_triangle	*triangle;
	t_objlst	*new;

	triangle = malloc(sizeof(t_triangle));
	if (!triangle)
		error_exit(d, E_MALLOC);
	new = objlst_new(d, triangle, tr);
	objlst_add_back(&d->objectlist, new);
	d->parse.check_range = false;
	triangle->v1 = parse_point(d, d->parse.elmnts[1], E_TR_1);
	triangle->v2 = parse_point(d, d->parse.elmnts[2], E_TR_2);
	triangle->v3 = parse_point(d, d->parse.elmnts[3], E_TR_3);
	triangle->vector = cross(subtract(triangle->v1, triangle->v2),
			subtract(triangle->v1, triangle->v3));
	if (length(triangle->vector) < EPSILON)
		error_exit(d, E_TR_VECTOR);
	triangle->color = parse_color(d, d->parse.elmnts[4], E_TR_4);
	new->phong = parse_phong(d, d->parse.elmnts[5], E_TR_MAT);
	set_range(d, 2.0, 1200);
	new->spec_exp = parse_int(d, d->parse.elmnts[6], E_TR_EXP);
}
