
#include "../incl/minirt.h"

t_intrsct	intersect_plane(t_ray ray, t_plane plane)
{
	double		divisor;
	double		result;
	t_intrsct	intersection;

	intersection.color = plane.color.trgb;
	divisor = dot(plane.vector, ray.direction);
	if (fabs(divisor) < EPSILON)
	{
		intersection.distance = INFINITY;
		return (intersection);
	}
	result = dot(subtract(plane.point, ray.origin), plane.vector) / divisor;
	if (result < EPSILON)
		intersection.distance = INFINITY;
	else
		intersection.distance = result;
	return (intersection);
}

t_intrsct	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_3d		oc;
	t_helper	h;
	t_intrsct	intersection;

	intersection.color = sphere.color.trgb;
	oc = subtract(ray.origin, sphere.center);
	h.a = dot(ray.direction, ray.direction);
	h.b = 2 * dot(ray.direction, oc);
	h.c = dot(oc, oc) - sphere.radius * sphere.radius;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < EPSILON)
		intersection.distance = INFINITY;
	else
		intersection.distance = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	return (intersection);
}

t_intrsct	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_intrsct	i;
	t_3d		u;
	t_3d		v;
	t_3d		oc;
	double		projection;
	t_helper	h;

	i.color = cylinder.color.trgb;
	projection = dot(ray.direction, cylinder.axis);
	if (fabs(projection) < EPSILON)
				return (i.distance = INFINITY, i);

	v = mult(cylinder.axis, projection);
	v = subtract(ray.direction, v);
	oc = subtract(ray.origin, cylinder.center);
	u = mult(cylinder.axis, dot(oc, cylinder.axis));
	u = subtract(oc, u);
	h.a = dot(v, v);
	h.b = 2 * dot(v, u);
	h.c = dot(u, u) - cylinder.radius * cylinder.radius;

	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < 0)
		return (i.distance = INFINITY, i);
	h.t1 = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	h.t2 = (-h.b + sqrt(h.discriminant)) / (2 * h.a);
	if (h.t2 < h.t1)
		printf("dafuq\n");	
	if (h.t1 > EPSILON)
		return (i.distance = h.t1, i);
	if (h.t2 > EPSILON)
		return (printf("dafuq\n"), i.distance = h.t2, i);
	return (i.distance = INFINITY, i);
}

t_intrsct	intersect_cylinder_asdf(t_ray ray, t_cylinder cylinder)
{
	t_3d		oc;
	t_helper	h;
	double		y_t1;
	double		y_t2;
	double		y_min;
	double		y_max;
	t_intrsct	intersection;

	intersection.color = cylinder.color.trgb;
	oc = subtract(ray.origin, cylinder.center);
	h.a = dot(ray.direction, ray.direction);
	h.b = 2 * dot(oc, ray.direction);
	h.c = dot(oc, oc) - cylinder.radius * cylinder.radius;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < 0)
		return (intersection.distance = INFINITY, intersection);
	h.t1 = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	h.t2 = (-h.b + sqrt(h.discriminant)) / (2 * h.a);
	if (h.t2 < 0)
		return (intersection.distance = INFINITY, intersection);
	y_t1 = ray.origin.y + h.t1 * ray.direction.y;
	y_t2 = ray.origin.y + h.t2 * ray.direction.y;
	y_min = cylinder.center.y;
	y_max = cylinder.center.y + cylinder.height;
	if ((y_t1 < y_min && y_t2 < y_min)
		|| (y_t1 > y_max && y_t2 > y_max))
		return (intersection.distance = INFINITY, intersection);
	if (y_t1 < y_min)
		h.t1 = (y_min - ray.origin.y) / ray.direction.y;
	else if (y_t1 > y_max)
		h.t1 = (y_max - ray.origin.y) / ray.direction.y;
	if (y_t2 < y_min)
		h.t2 = (y_min - ray.origin.y) / ray.direction.y;
	else if (y_t2 > y_max)
		h.t2 = (y_max - ray.origin.y) / ray.direction.y;
	if (h.t1 > h.t2)
		return (intersection.distance = INFINITY, intersection);
	if (h.t1 < 0)
	{
		if (h.t2 < 0)
			return (intersection.distance = INFINITY, intersection);
		return (intersection.distance = h.t2, intersection);
	}
	return (intersection.distance = h.t1, intersection);
}




t_intrsct	intersect_cylinder_saveoldwork(t_ray ray, t_cylinder cylinder)
{
	t_3d		oc;
	t_helper	h;
	double		y_t1;
	double		y_t2;
	double		y_min;
	double		y_max;
	t_intrsct	intersection;

	intersection.color = cylinder.color.trgb;
	oc = subtract(ray.origin, cylinder.center);
	h.a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	h.b = 2 * (oc.x * ray.direction.x + oc.z * ray.direction.z);
	h.c = oc.x * oc.x + oc.z * oc.z - cylinder.radius * cylinder.radius;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < 0)
		return (intersection.distance = INFINITY, intersection);
	h.t1 = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	h.t2 = (-h.b + sqrt(h.discriminant)) / (2 * h.a);
	if (h.t2 < 0)
		return (intersection.distance = INFINITY, intersection);
	y_t1 = ray.origin.y + h.t1 * ray.direction.y;
	y_t2 = ray.origin.y + h.t2 * ray.direction.y;
	y_min = cylinder.center.y;
	y_max = cylinder.center.y + cylinder.height;
	if ((y_t1 < y_min && y_t2 < y_min)
		|| (y_t1 > y_max && y_t2 > y_max))
		return (intersection.distance = INFINITY, intersection);
	if (y_t1 < y_min)
		h.t1 = (y_min - ray.origin.y) / ray.direction.y;
	else if (y_t1 > y_max)
		h.t1 = (y_max - ray.origin.y) / ray.direction.y;
	if (y_t2 < y_min)
		h.t2 = (y_min - ray.origin.y) / ray.direction.y;
	else if (y_t2 > y_max)
		h.t2 = (y_max - ray.origin.y) / ray.direction.y;
	if (h.t1 > h.t2)
		return (intersection.distance = INFINITY, intersection);
	if (h.t1 < 0)
	{
		if (h.t2 < 0)
			return (intersection.distance = INFINITY, intersection);
		return (intersection.distance = h.t2, intersection);
	}
	return (intersection.distance = h.t1, intersection);
}
