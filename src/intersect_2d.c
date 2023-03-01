
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
