
#include "../incl/minirt.h"

t_3d	get_normal_sphere(t_3d point, void *obj)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)obj;
	return (norm(subtract(point, sphere->center)));
}

t_3d	get_normal_cylinder(t_3d point, void *obj)
{
	t_cylinder	*cylinder;
	t_3d		base_to_point;
	double		projection;
	t_3d		local_center;

	cylinder = (t_cylinder *)obj;
	base_to_point = subtract(point, cylinder->base);
	projection = dot(base_to_point, cylinder->axis);
	local_center = add(cylinder->base, mult(cylinder->axis, projection));
	return(norm(subtract(point, local_center)));
}

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