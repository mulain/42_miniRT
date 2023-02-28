
#include "../incl/minirt.h"

t_intrsct	intersect_plane(t_ray ray, t_plane plane)
{
	double		divisor;
	double		result;
	t_intrsct	i;

	i.color = plane.color;
	divisor = dot(plane.vector, ray.direction);
	if (fabs(divisor) < EPSILON)
		return (i.distance = INFINITY, i);
	result = dot(subtract(plane.point, ray.origin), plane.vector) / divisor;
	if (result < EPSILON)
		i.distance = INFINITY;
	else
		i.distance = result;
	return (i);
}

t_intrsct	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_3d		oc;
	t_helper	h;
	t_intrsct	i;

	i.color = sphere.color;
	oc = subtract(ray.origin, sphere.center);
	h.a = dot(ray.direction, ray.direction);
	h.b = 2 * dot(ray.direction, oc);
	h.c = dot(oc, oc) - sphere.radius * sphere.radius;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < EPSILON)
		i.distance = INFINITY;
	else
		i.distance = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	return (i);
}

t_intrsct	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_intrsct	i;
	double		t_tube;
	double		t_caps;

	i.color = cylinder.color;
	t_tube = cylinder_tube(ray, cylinder);
	t_caps = cylinder_caps(ray, cylinder);
	i.distance = fmin(t_tube, t_caps);
	return (i);
}

double	cylinder_tube(t_ray ray, t_cylinder cylinder)
{
	t_helper	h;
	t_3d		v;
	t_3d		u;
	t_3d		oc;

	v = mult(cylinder.axis, dot(ray.direction, cylinder.axis));
	v = subtract(ray.direction, v);
	oc = subtract(ray.origin, cylinder.base);
	u = mult(cylinder.axis, dot(oc, cylinder.axis));
	u = subtract(oc, u);
	h.a = dot(v, v);
	h.b = 2 * dot(v, u);
	h.c = dot(u, u) - cylinder.radius * cylinder.radius;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < EPSILON)
		return (INFINITY);
	h.t1 = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	if (h.t1 < EPSILON)
		return (INFINITY);
	h.intrsct = add(ray.origin, mult(ray.direction, h.t1));
	h.intrsct = subtract(h.intrsct, cylinder.base);
	h.dot_prod = dot(h.intrsct, cylinder.axis);
	if (h.dot_prod < EPSILON || h.dot_prod > cylinder.height)
		return (INFINITY);
	return (h.t1);
}

double	cylinder_caps(t_ray ray, t_cylinder cylinder)
{
	double		t_top;
	double		t_base;
	t_plane		cap;
	t_3d		intrsct;

	cap.color.trgb = 0x0;
	cap.point = cylinder.top;
	cap.vector = cylinder.axis;
	t_top = intersect_plane(ray, cap).distance;
	intrsct = add(ray.origin, mult(ray.direction, t_top));
	if (distance(intrsct, cylinder.top) > cylinder.radius)
		t_top = INFINITY;
	cap.point = cylinder.base;
	t_base = intersect_plane(ray, cap).distance;
	intrsct = add(ray.origin, mult(ray.direction, t_base));
	if (distance(intrsct, cylinder.base) > cylinder.radius)
		t_base = INFINITY;
	return (fmin(t_top, t_base));
}
