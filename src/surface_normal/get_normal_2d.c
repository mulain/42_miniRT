
#include "../incl/minirt.h"

t_3d	normal_plane(t_3d point, t_3d ray_origin, void *obj)
{
	t_plane		*plane;
	t_3d		to_ray_origin;

	plane = (t_plane *)obj;
	to_ray_origin = subtract(ray_origin, point);
	if (dot(to_ray_origin, plane->vector) < EPSILON)
		return (reverse(plane->vector));
	return (plane->vector);
}

t_3d	normal_disc(t_3d point, t_3d ray_origin, void *obj)
{
	t_disc		*disc;
	t_3d		to_ray_origin;

	disc = (t_disc *)obj;
	to_ray_origin = subtract(ray_origin, point);
	if (dot(to_ray_origin, disc->vector) < EPSILON)
		return (reverse(disc->vector));
	return (disc->vector);
}

t_3d	normal_triangle(t_3d point, t_3d ray_origin, void *obj)
{
	t_triangle	*triangle;
	t_3d		to_ray_origin;

	triangle = (t_triangle *)obj;
	to_ray_origin = subtract(ray_origin, point);
	if (dot(to_ray_origin, triangle->vector) < EPSILON)
		return (reverse(triangle->vector));
	return (triangle->vector);
}
