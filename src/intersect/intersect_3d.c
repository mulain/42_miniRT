
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
	i.point = add(ray.origin, scale(ray.direction, i.distance));
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
	i.distance = solve_quad(h.a, h.b, h.c, NULL);
	if (i.distance == INFINITY)
		return (i);
	i.point = add(ray.origin, scale(ray.direction, i.distance));
	return (i);
}

/*
ray_tr is used as an array of 2 doubles.
The direction is actually translated, but ray.origin is not really
a translation of the origin.
*/
t_intrsct	intersect_tube(t_ray ray, void *obj)
{
	t_tube		*tube;
	t_intrsct	i;
	t_helper	h;
	t_ray		ray_tr;

	tube = (t_tube *)obj;
	i.color = tube->color;
	ray_tr.direction = translate(tube->axis, ray.direction);
	ray_tr.origin = translate(tube->axis, subtract(ray.origin, tube->base));
	h.a = dot(ray_tr.direction, ray_tr.direction);
	h.b = 2 * dot(ray_tr.direction, ray_tr.origin);
	h.c = dot(ray_tr.origin, ray_tr.origin) - tube->radius * tube->radius;
	i.distance = solve_quad(h.a, h.b, h.c, NULL);
	if (i.distance == INFINITY)
		return (i);
	i.point = add(ray.origin, scale(ray.direction, i.distance));
	if (!is_withinbounds(i.point, tube->base, tube->axis, tube->height))
		i.distance = INFINITY;
	return (i);
}

t_intrsct	intersect_cone(t_ray ray, void *obj)
{
	t_cone		*cone;
	t_intrsct	i;
	t_helper	h;
	double		m;
	double		dot1;
	double		dot2;
	double		t[2];

	cone = (t_cone *)obj;
	i.color = cone->color;
	m = (cone->radius * cone->radius) / (cone->height * cone->height);
	h.oc = subtract(ray.origin, cone->apex);
	dot1 = dot(ray.direction, cone->axis);
	dot2 = dot(ray.direction, h.oc);
	h.a = dot(ray.direction, ray.direction) - m * dot1 * dot1 - dot1 * dot1;
	h.b = 2 * (dot2 - m * dot1 * dot(h.oc, cone->axis) - dot1 * dot(h.oc, cone->axis));
	h.c = dot(h.oc, h.oc) - m * dot(h.oc, cone->axis) * dot(h.oc, cone->axis) - dot(h.oc, cone->axis) * dot(h.oc, cone->axis);
	i.distance = solve_quad(h.a, h.b, h.c, t);
	if (i.distance == INFINITY)
		return(i);
	i.point = add(ray.origin, scale(ray.direction, t[0]));
	if (!(t[0] < EPSILON)
		&& is_withinbounds(i.point, cone->base, cone->axis, cone->height))
		return (i.distance = t[0], i);
	i.point = add(ray.origin, scale(ray.direction, t[1]));
	if (is_withinbounds(i.point, cone->base, cone->axis, cone->height))
		return (i.distance = t[1], i);
	return (i.distance = INFINITY, i);

	/* double	discriminant;
	double	t1;
	double	t2;

	discriminant = h.b * h.b - 4 * h.a * h.c;
	if (discriminant < EPSILON)
		return (i.distance = INFINITY, i);
	t1 = (-h.b - sqrt(discriminant)) / (2 * h.a);
	t2 = (-h.b + sqrt(discriminant)) / (2 * h.a);
	if (t1 < EPSILON && t2 < EPSILON)
		return (i.distance = INFINITY, i);
	i.point = add(ray.origin, scale(ray.direction, t1));
	if (!(t1 < EPSILON)
		&& is_withinbounds(i.point, cone->base, cone->axis, cone->height))
		return (i.distance = t1, i);
	i.point = add(ray.origin, scale(ray.direction, t2));
	if (is_withinbounds(i.point, cone->base, cone->axis, cone->height))
		return (i.distance = t2, i);
	return (i.distance = INFINITY, i); */
}
