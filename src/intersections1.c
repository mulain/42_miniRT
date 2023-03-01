
#include "../incl/minirt.h"

t_intrsct	intersect_plane(t_ray ray, void *obj)
{
	t_plane		*plane;
	t_intrsct	i;
	double		div;

	plane = (t_plane *)obj;
	i.color = plane->color;
	div = dot(plane->vector, ray.direction);
	if (fabs(div) < EPSILON)
		return (i.distance = INFINITY, i);
	i.distance = dot(subtract(plane->point, ray.origin), plane->vector) / div;
	if (i.distance < EPSILON)
		return (i.distance = INFINITY, i);
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	return (i);
}

t_intrsct	intersect_disc(t_ray ray, void *obj)
{
	t_disc		*disc;
	t_intrsct	i;
	t_plane		disc_plane;

	disc = (t_disc *)obj;
	disc_plane.point = disc->center;
	disc_plane.vector = disc->vector;
	disc_plane.color = disc->color;
	i = intersect_plane(ray, &disc_plane);
	if (distance(i.point, disc->center) > disc->radius)
		i.distance = INFINITY;
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
	t_disc		disc;

	cylinder = (t_cylinder *)obj;
	i_tube = intersect_tube(ray, cylinder);
	disc.center = cylinder->top;
	disc.vector = cylinder->axis;
	disc.radius = cylinder->radius;
	disc.color = cylinder->color;
	i_top = intersect_disc(ray, &disc);
	disc.center = cylinder->base;
	i_base = intersect_disc(ray, &disc);
	if (i_tube.distance < i_top.distance && i_tube.distance < i_base.distance)
		return (i_tube);
	if (i_top.distance < i_base.distance)
		return (i_top);
	return (i_base);
}

t_intrsct	intersect_tube(t_ray ray, void *obj)
{
	t_intrsct	i;
	t_helper	h;
	t_3d		translate[2];
	double		length;
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)obj;
	i.color = cylinder->color;
	translate[0] = mult(cylinder->axis, dot(ray.direction, cylinder->axis));
	translate[0] = subtract(ray.direction, translate[0]);
	h.oc = subtract(ray.origin, cylinder->base);
	translate[1] = mult(cylinder->axis, dot(h.oc, cylinder->axis));
	translate[1] = subtract(h.oc, translate[1]);
	h.a = dot(translate[0], translate[0]);
	h.b = 2 * dot(translate[0], translate[1]);
	h.c = dot(translate[1], translate[1]) - cylinder->radius * cylinder->radius;
	i.distance = solve_quad(h.a, h.b, h.c);
	if (i.distance == INFINITY)
		return (i);
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	length = dot(subtract(i.point, cylinder->base), cylinder->axis);
	if (length < EPSILON || length - cylinder->height > EPSILON)
		i.distance = INFINITY;
	return (i);
}
