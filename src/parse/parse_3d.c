
#include "../incl/minirt.h"

void	parse_sphere(t_data *d)
{
	t_sphere	*sphere;
	t_objlst	*new;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_exit(d, E_MALLOC);
	new = objlst_new(d, sphere, sp);
	objlst_add_back(&d->objectlist, new);
	d->parse.check_range = false;
	sphere->center = parse_point(d, d->parse.elmnts[1], E_SP_1);
	sphere->radius = 0.5 * parse_double(d, d->parse.elmnts[2], E_SP_2);
	sphere->color = parse_color(d, d->parse.elmnts[3], E_SP_3);
	new->phong = parse_phong(d, d->parse.elmnts[4], E_SP_MAT);
	set_range(d, 2.0, 1200);
	new->spec_exp = parse_int(d, d->parse.elmnts[5], E_SP_EXP);
}

void	parse_cylinder(t_data *d)
{
	t_tube		*tube;
	t_disc		*disc[2];
	t_objlst	*new[3];

	tube = malloc(sizeof(t_tube));
	disc[0] = malloc(sizeof(t_disc));
	disc[1] = malloc(sizeof(t_disc));
	if (!tube || !disc[0] || !disc[1])
		error_exit(d, E_MALLOC);
	d->parse.check_range = false;
	new[0] = objlst_new(d, tube, tu);
	objlst_add_back(&d->objectlist, new[0]);
	new[1] = objlst_new(d, disc[0], di);
	objlst_add_back(&d->objectlist, new[1]);
	new[2] = objlst_new(d, disc[1], di);
	objlst_add_back(&d->objectlist, new[2]);
	tube->base = parse_point(d, d->parse.elmnts[1], E_CY_1);
	tube->axis = parse_vector(d, d->parse.elmnts[2], E_CY_2);
	tube->radius = 0.5 * parse_double(d, d->parse.elmnts[3], E_CY_3);
	tube->height = parse_double(d, d->parse.elmnts[4], E_CY_4);
	tube->top = add(tube->base, scale(tube->axis, tube->height));
	tube->color = parse_color(d, d->parse.elmnts[5], E_CY_5);
	new[0]->phong = parse_phong(d, d->parse.elmnts[6], E_CY_MAT);
	new[1]->phong = new[0]->phong;
	new[2]->phong = new[0]->phong;
	set_range(d, 2.0, 1200);
	new[0]->spec_exp = parse_int(d, d->parse.elmnts[7], E_CY_EXP);
	new[1]->spec_exp = new[0]->spec_exp;
	new[2]->spec_exp= new[0]->spec_exp;
	*disc[0] = (t_disc){tube->top, tube->axis, tube->radius, tube->color};
	*disc[1] = (t_disc){tube->base, tube->axis, tube->radius, tube->color};
}

void	parse_cone(t_data *d)
{
	t_cone		*cone;
	t_disc		*disc_base;
	t_objlst	*new[2];

	cone = malloc(sizeof(t_cone));
	disc_base = malloc(sizeof(t_disc));
	if (!cone || !disc_base)
		error_exit(d, E_MALLOC);
	d->parse.check_range = false;
	new[0] = objlst_new(d, cone, co);
	objlst_add_back(&d->objectlist, new[0]);
	new[1] = objlst_new(d, disc_base, di);
	objlst_add_back(&d->objectlist, new[1]);
	cone->base = parse_point(d, d->parse.elmnts[1], E_CONE1);
	cone->axis = parse_vector(d, d->parse.elmnts[2], E_CONE2);
	cone->radius = 0.5 * parse_double(d, d->parse.elmnts[3], E_CONE3);
	cone->height = parse_double(d, d->parse.elmnts[4], E_CONE4);
	cone->apex = add(cone->base, scale(cone->axis, cone->height));
	cone->color = parse_color(d, d->parse.elmnts[5], E_CONE5);
	new[0]->phong = parse_phong(d, d->parse.elmnts[6], E_CONEMAT);
	new[1]->phong = new[0]->phong;
	*disc_base = (t_disc){cone->base, cone->axis, cone->radius, cone->color};
	set_range(d, 2.0, 1200);
	new[0]->spec_exp = parse_int(d, d->parse.elmnts[7], E_CONEEXP);
	new[1]->spec_exp = new[0]->spec_exp;
}
