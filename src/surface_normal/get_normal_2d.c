
#include "../incl/minirt.h"

t_3d	get_normal_plane(t_3d point, t_3d light, void *obj)
{
	t_plane		*plane;
	t_3d		to_light;

	plane = (t_plane *)obj;
	to_light = subtract(light, point);
	if (dot(to_light, plane->vector) < EPSILON)
		return (reverse(plane->vector));
	return (plane->vector);
}

t_3d	get_normal_disc(t_3d point, t_3d light, void *obj)
{
	t_disc		*disc;
	t_3d		to_light;

	disc = (t_disc *)obj;
	to_light = subtract(light, point);
	if (dot(to_light, disc->vector) < EPSILON)
		return (reverse(disc->vector));
	return (disc->vector);
}

t_3d	get_normal_triangle(t_3d point, t_3d light, void *obj)
{
	t_triangle	*triangle;
	t_3d		to_light;

	triangle = (t_triangle *)obj;
	to_light = subtract(light, point);
	if (dot(to_light, triangle->vector) < EPSILON)
		return (reverse(triangle->vector));
	return (triangle->vector);
}
