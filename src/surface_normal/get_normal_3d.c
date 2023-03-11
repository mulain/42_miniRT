
#include "../incl/minirt.h"

t_3d	get_normal_sphere(t_3d point, t_3d light, void *obj)
{
	t_sphere	*sphere;

	(void)light;
	sphere = (t_sphere *)obj;
	return (norm(subtract(point, sphere->center)));
}

t_3d	get_normal_tube(t_3d point, t_3d light, void *obj)
{
	t_tube		*tube;
	t_3d		base_to_point;
	double		projection;
	t_3d		local_center;

	(void)light;
	tube = (t_tube *)obj;
	base_to_point = subtract(point, tube->base);
	projection = dot(base_to_point, tube->axis);
	local_center = add(tube->base, scale(tube->axis, projection));
	return (norm(subtract(point, local_center)));
}

t_3d	get_normal_cone(t_3d point, t_3d light, void *obj)
{
	t_cone		*cone;
	t_3d		bp;
	t_3d		ap;
	t_3d		vector;

	(void)light;
	cone = (t_cone *)obj;
	bp = subtract(point, cone->base);
	ap = subtract(point, cone->apex);
	vector = scale(ap, dot(bp, ap) / dot(ap, ap));
	vector = subtract(bp, vector);
	return (norm(vector));
}
