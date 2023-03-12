
#include "../incl/minirt.h"

t_3d	get_normal_sphere(t_3d point, t_3d light, void *obj)
{
	t_sphere	*sphere;
	t_3d		p_to_light;
	t_3d		center_to_p;

	sphere = (t_sphere *)obj;
	p_to_light = subtract(light, point);
	center_to_p = subtract(point, sphere->center);
	if (dot(p_to_light, center_to_p) < EPSILON)
		return (norm(reverse(center_to_p)));
	return (norm(center_to_p));
}

t_3d	get_normal_tube(t_3d point, t_3d light, void *obj)
{
	t_tube		*tube;
	double		projection;
	t_3d		p_to_light;
	t_3d		local_center;
	t_3d		lcenter_to_point;

	tube = (t_tube *)obj;
	p_to_light = subtract(light, point);
	projection = dot(subtract(point, tube->base), tube->axis);
	local_center = add(tube->base, scale(tube->axis, projection));
	lcenter_to_point = subtract(point, local_center);
	if (dot(p_to_light, lcenter_to_point) < EPSILON)
		return (norm(reverse(lcenter_to_point)));
	return (norm(lcenter_to_point));
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
