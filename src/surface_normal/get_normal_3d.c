
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

/* t_3d	get_normal_cone_old(t_3d point, t_3d light, void *obj)
{
	t_cone		*cone;
	t_3d		point_to_base;
	double		height;
	double		radius_at_point;

	(void)light;
	cone = (t_cone *)obj;
	point_to_base = subtract(point, cone->base);
	height = dot(point_to_base, cone->axis)  / norm(cone.axis);
	radius_at_point = cone->radius * height / cone->height;

	t_3d		tangent;
	t_3d		normal_to_base;
	tangent = subtract(point, cone->base);
	normal_to_base = subtract(tangent, scale(cone->axis, dot(tangent, cone->axis) / dot(cone->axis, cone->axis)));
    normal = multiply(normal_to_base, -1 / norm(normal_to_base));
    return normal;
}
*/

t_3d	get_normal_cone(t_3d point, t_3d light, void *obj)
{
	t_cone		*cone;
	double		len_hypo;
	t_3d		a;

	(void)light;
	cone = (t_cone *)obj;
	len_hypo = to_deg(cos(cone->theta_rad)) / distance(point, cone->apex);
	a = add(cone->apex, scale(cone->axis, -len_hypo));
	return (norm(subtract(point, a)));
}


/* t_3d cone_surface_normal(t_cone cone, t_3d point_on_cone) {
    // Calculate height and radius at point
    t_3d point_to_base = subtract(point_on_cone, cone.base);
    double height = dot_product(point_to_base, cone.axis) / norm(cone.axis);
    double radius_at_base = cone.radius;
    double radius_at_point = radius_at_base * height / cone.height;

    // Calculate normal
    t_3d normal;
    if (radius_at_point >= radius_at_base)
	{
        // Cone is widening, use tip normal
        t_3d point_to_tip = subtract(cone.apex, point_on_cone);
        t_3d normal_to_tip = subtract(point_to_tip, multiply(cone.axis, dot_product(point_to_tip, cone.axis) / dot_product(cone.axis, cone.axis)));
        normal = multiply(normal_to_tip, 1 / norm(normal_to_tip));
    } else {
        // Cone is narrowing, use base normal
        t_3d tangent = subtract(point_on_cone, cone.base);
        t_3d normal_to_base = subtract(tangent, multiply(cone.axis, dot_product(tangent, cone.axis) / dot_product(cone.axis, cone.axis)));
        normal = multiply(normal_to_base, -1 / norm(normal_to_base));
    }
    return normal;
} */
