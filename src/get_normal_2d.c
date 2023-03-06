
#include "../incl/minirt.h"

t_3d	get_normal_plane(t_3d point, void *obj)
{
	t_plane		*plane;

	plane = (t_plane *)obj;
	(void)point;
	return (plane->vector);
}

t_3d	get_normal_disc(t_3d point, void *obj)
{
	t_disc		*disc;

	disc = (t_disc *)obj;
	(void)point;
	return (disc->vector);
}

t_3d	get_normal_triangle(t_3d point, void *obj)
{
	t_triangle	*triangle;

	triangle = (t_triangle *)obj;
	(void)point;
	return (triangle->vector);
}
