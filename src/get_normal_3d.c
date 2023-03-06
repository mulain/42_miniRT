
#include "../incl/minirt.h"

t_3d	get_normal_sphere(t_3d point, void *obj)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)obj;
	return (norm(subtract(point, sphere->center)));
}

t_3d	get_normal_tube(t_3d point, void *obj)
{
	t_tube		*tube;
	t_3d		base_to_point;
	double		projection;
	t_3d		local_center;

	tube = (t_tube *)obj;
	base_to_point = subtract(point, tube->base);
	projection = dot(base_to_point, tube->axis);
	local_center = add(tube->base, mult(tube->axis, projection));
	return(norm(subtract(point, local_center)));
}
