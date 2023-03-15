
#include "../incl/minirt.h"

t_3d	normal_sphere(t_3d point, t_3d ray_origin, void *obj)
{
	t_sphere	*sphere;
	t_3d		p_to_ray_origin;
	t_3d		center_to_p;

	sphere = (t_sphere *)obj;
	p_to_ray_origin = subtract(ray_origin, point);
	center_to_p = subtract(point, sphere->center);
	if (dot(p_to_ray_origin, center_to_p) < EPSILON)
		return (norm(reverse(center_to_p)));
	return (norm(center_to_p));
}

t_3d	normal_tube(t_3d point, t_3d ray_origin, void *obj)
{
	t_tube		*tube;
	double		projection;
	t_3d		p_to_ray_origin;
	t_3d		local_center;
	t_3d		lcenter_to_point;

	tube = (t_tube *)obj;
	p_to_ray_origin = subtract(ray_origin, point);
	projection = dot(subtract(point, tube->base), tube->axis);
	local_center = add(tube->base, scale(tube->axis, projection));
	lcenter_to_point = subtract(point, local_center);
	if (dot(p_to_ray_origin, lcenter_to_point) < EPSILON)
		return (norm(reverse(lcenter_to_point)));
	return (norm(lcenter_to_point));
}

t_3d	normal_cone(t_3d point, t_3d ray_origin, void *obj)
{
	t_cone		*cone;
	t_3d		p_to_ray_origin;
	t_3d		bp;
	t_3d		ap;
	t_3d		vector;

	cone = (t_cone *)obj;
	p_to_ray_origin = subtract(ray_origin, point);
	bp = subtract(point, cone->base);
	ap = subtract(point, cone->apex);
	vector = scale(ap, dot(bp, ap) / dot(ap, ap));
	vector = subtract(bp, vector);
	if (dot(p_to_ray_origin, vector) < EPSILON)
		return (norm(reverse(vector)));
	return (norm(vector));
}
