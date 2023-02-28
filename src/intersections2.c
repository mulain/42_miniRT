
#include "../incl/minirt.h"

t_intrsct	intersect_cone(t_ray ray, t_cone cone)
{
	t_3d		oc;
	t_helper	h;
	t_intrsct	i;

	i.color = sphere.color.trgb;
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
