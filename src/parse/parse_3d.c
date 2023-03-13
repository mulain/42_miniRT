
#include "../incl/minirt.h"

void	parse_sphere(t_data *d)
{
	t_sphere	*sphere;
	t_surface	surface;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_exit(d, E_MALLOC);
	d->parse.min = 0;
	d->parse.max = 5;
	surface = parse_int(d, d->parse.elmnts[4], E_SPHEREMAT);
	objlst_add_back(&d->objectlist, objlst_new(d, sphere, sp, surface));
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
	t_surface	surface;

	tube = malloc(sizeof(t_tube));
	disc_top = malloc(sizeof(t_disc));
	disc_base = malloc(sizeof(t_disc));
	if (!tube || !disc_top || !disc_base)
		error_exit(d, E_MALLOC);
	d->parse.min = 0;
	d->parse.max = 5;
	surface = parse_int(d, d->parse.elmnts[6], E_CYLINDERMAT);
	objlst_add_back(&d->objectlist, objlst_new(d, tube, tu, surface));
	objlst_add_back(&d->objectlist, objlst_new(d, disc_top, di, surface));
	objlst_add_back(&d->objectlist, objlst_new(d, disc_base, di, surface));
	tube->base = parse_point(d, d->parse.elmnts[1], E_CYLINDER1);
	tube->axis = parse_vector(d, d->parse.elmnts[2], E_CYLINDER2);
	d->parse.min = 0.0;
	d->parse.max = 0.0;
	tube->radius = 0.5 * parse_double(d, d->parse.elmnts[3], E_CYLINDER3);
	tube->height = parse_double(d, d->parse.elmnts[4], E_CYLINDER4);
	tube->top = add(tube->base, scale(tube->axis, tube->height));
	tube->color = parse_color(d, d->parse.elmnts[5], E_CYLINDER5);
	*disc_top = (t_disc){tube->top, tube->axis, tube->radius, tube->color};
	*disc_base = (t_disc){tube->base, tube->axis, tube->radius, tube->color};
}

/*
Theta is half of the angle at the cone's apex, defining a 90° triangle
with the side of the cone as hypotenuse, the radius as the opposite and
the height as the adjacent.
*/
void	parse_cone(t_data *d)
{
	t_cone	*cone;
	t_disc	*disc_base;
	t_surface	surface;

	cone = malloc(sizeof(t_cone));
	disc_base = malloc(sizeof(t_disc));
	if (!cone || !disc_base)
		error_exit(d, E_MALLOC);
	d->parse.min = 0;
	d->parse.max = 5;
	surface = parse_int(d, d->parse.elmnts[6], E_CONEMAT);
	objlst_add_back(&d->objectlist, objlst_new(d, cone, co, surface));
	objlst_add_back(&d->objectlist, objlst_new(d, disc_base, di, surface));
	cone->base = parse_point(d, d->parse.elmnts[1], E_CONE1);
	cone->axis = (parse_vector(d, d->parse.elmnts[2], E_CONE2));
	d->parse.min = 0.0;
	d->parse.max = 0.0;
	cone->radius = 0.5 * parse_double(d, d->parse.elmnts[3], E_CONE3);
	cone->height = parse_double(d, d->parse.elmnts[4], E_CONE4);
	cone->apex = add(cone->base, scale(cone->axis, cone->height));
	cone->theta_rad = atan(cone->radius / cone->height);
	cone->theta_deg = to_deg(cone->theta_rad);
	cone->color = parse_color(d, d->parse.elmnts[5], E_CONE5);
	*disc_base = (t_disc){cone->base, cone->axis, cone->radius, cone->color};
}
