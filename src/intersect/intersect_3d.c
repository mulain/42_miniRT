
#include "../incl/minirt.h"

t_intrsct	intersect_sphere(t_ray ray, void *obj)
{
	t_sphere	*sphere;
	t_intrsct	i;

	t_3d		l;
	double		tca;
	double		d2;
	double		thc;
	double		t1;
	double		t2;

	sphere = (t_sphere *)obj;
	i.color = sphere->color;
	l = subtract(sphere->center, ray.origin);
	tca = dot(l, ray.direction);
	if (tca < EPSILON)
		return (i.distance = INFINITY, i);
	d2 = dot(l, l) - tca * tca;
	if (d2 - sphere->radius * sphere->radius > EPSILON)
		return (i.distance = INFINITY, i);
	thc = sqrt(sphere->radius * sphere->radius - d2);
	t1 = tca - thc;
	t2 = tca + thc;
	if (t1 < EPSILON)
	{
		if (t2 < EPSILON)
			return (i.distance = INFINITY, i);
		i.distance = t2;
	}
	else
		i.distance = t1;
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	return (i);
}

t_intrsct	intersect_sphere_old(t_ray ray, void *obj)
{
	t_sphere	*sphere;
	t_intrsct	i;
	t_helper	h;

	sphere = (t_sphere *)obj;
	i.color = sphere->color;
	h.oc = subtract(ray.origin, sphere->center);
	h.a = dot(ray.direction, ray.direction);
	h.b = 2 * dot(ray.direction, h.oc);
	h.c = dot(h.oc, h.oc) - sphere->radius * sphere->radius;
	i.distance = solve_quad(h.a, h.b, h.c);
	if (i.distance == INFINITY)
		return (i);
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	return (i);
}

t_intrsct	intersect_tube(t_ray ray, void *obj)
{
	t_tube		*tube;
	t_intrsct	i;
	t_helper	h;
	t_3d		translate[2];
	double		length;

	tube = (t_tube *)obj;
	i.color = tube->color;
	translate[0] = mult(tube->axis, dot(ray.direction, tube->axis));
	translate[0] = subtract(ray.direction, translate[0]);
	h.oc = subtract(ray.origin, tube->base);
	translate[1] = mult(tube->axis, dot(h.oc, tube->axis));
	translate[1] = subtract(h.oc, translate[1]);
	h.a = dot(translate[0], translate[0]);
	h.b = 2 * dot(translate[0], translate[1]);
	h.c = dot(translate[1], translate[1]) - tube->radius * tube->radius;
	i.distance = solve_quad(h.a, h.b, h.c);
	if (i.distance == INFINITY)
		return (i);
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	length = dot(subtract(i.point, tube->base), tube->axis);
	if (length < EPSILON || length - tube->height > EPSILON)
		i.distance = INFINITY;
	return (i);
}

/* t_intrsct	intersect_cone(t_ray ray, void *obj)
{
	t_cone		*cone;
	t_intrsct	i;
	t_helper	h;
	t_3d		oc;

	cone = (t_cone *)obj;
	i.color = sphere.color.trgb;
	oc = subtract(ray.origin, cone->base);
	h.a = dot(ray.direction, ray.direction);
	h.b = 2 * dot(ray.direction, oc);
	h.c = dot(oc, oc) - sphere.radius * sphere.radius;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < EPSILON)
		i.distance = INFINITY;
	else
		i.distance = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	return (i);
} */

void cylinder_to_cone(cylinder *c, cone *cn) {
    cn->axis = vector_normalize(c->axis);
    cn->apex = vector_add(c->center, vector_scale(cn->axis, c->radius / tan(cn->angle / 2)));
    double d = vector_distance(c->center, cn->apex);
    cn->angle = atan(c->radius / d);