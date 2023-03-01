
#include "../incl/minirt.h"

t_intrsct	intersect_plane(t_ray ray, void *obj)
{
	t_plane		*plane;
	t_intrsct	i;
	double		divisor;

	plane = (t_plane *)obj;
	i.color = plane->color;
	divisor = dot(plane->vector, ray.direction);
	if (fabs(divisor) < EPSILON)
		return (i.distance = INFINITY, i);
	i.distance = dot(subtract(plane->point, ray.origin), plane->vector) / divisor;
	if (i.distance < EPSILON)
		return (i.distance = INFINITY, i);
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	return (i);
}

t_intrsct	intersect_sphere(t_ray ray, void *obj)
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
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	return (i);
}

t_intrsct	intersect_cylinder(t_ray ray, void *obj)
{
	t_cylinder	*cylinder;
	t_intrsct	i_tube;
	t_intrsct	i_top;
	t_intrsct	i_base;
	t_plane		disc_plane;

	cylinder = (t_cylinder *)obj;
	i_tube = intersect_tube(ray, cylinder);
	disc_plane = (t_plane){cylinder->top, cylinder->axis, cylinder->color};
	i_top = intersect_disc(ray, &disc_plane, cylinder->radius);
	disc_plane.point = cylinder->base;
	i_base = intersect_disc(ray, &disc_plane, cylinder->radius);
	if (i_tube.distance < i_top.distance && i_tube.distance < i_base.distance)
		return (i_tube);
	if (i_top.distance < i_base.distance)
		return (i_top);
	return (i_base);
}

t_intrsct	intersect_tube(t_ray ray, t_cylinder *cylinder)
{
	t_intrsct	i;
	t_helper	h;
	t_3d		v;
	t_3d		u;
	double		length;

	i.color = cylinder->color;
	v = mult(cylinder->axis, dot(ray.direction, cylinder->axis));
	v = subtract(ray.direction, v);
	h.oc = subtract(ray.origin, cylinder->base);
	u = mult(cylinder->axis, dot(h.oc, cylinder->axis));
	u = subtract(h.oc, u);
	h.a = dot(v, v);
	h.b = 2 * dot(v, u);
	h.c = dot(u, u) - cylinder->radius * cylinder->radius;
	i.distance = solve_quad(h.a, h.b, h.c);
	if (i.distance == INFINITY)
		return (i);
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	length = dot(subtract(i.point, cylinder->base), cylinder->axis);
	if (length < EPSILON || length - cylinder->height > EPSILON)
		i.distance = INFINITY;
	return (i);
}

t_intrsct	intersect_disc(t_ray ray, t_plane *plane, double radius)
{
	t_intrsct	i;

	i = intersect_plane(ray, plane);
	if (distance(i.point, plane->point) > radius)
		i.distance = INFINITY;
	return (i);
}
