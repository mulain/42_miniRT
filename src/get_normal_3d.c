
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
	return (norm(subtract(point, local_center)));
}

t_3d	get_normal_cone(t_3d point, void *obj)
{
	t_cone		*cone;
	t_3d		dist_to_point;
	double		distance;
	t_3d		w;
	t_3d		axis_dir;

	cone = (t_cone *)obj;
	dist_to_point = subtract(point, cone->base);
	distance = dot(dist_to_point, cone->axis) / dot(cone->axis, cone->axis);
	w = subtract(dist_to_point, mult(cone->axis, distance));
	axis_dir.x = w.x;
	axis_dir.y = w.y;
	axis_dir.z = 0;
	double cos_theta = dot(axis_dir, cone->axis) / (sqrt(dot(axis_dir, axis_dir)) * sqrt(dot(cone->axis, cone->axis)));
	t_3d normal = subtract(axis_dir, mult(cone->axis, cos_theta));

	return (norm(normal));
}


/* oid surface_normal(t_3d point, t_3d* normal) {
    // Calculate the distance from the point to the cylinder axis
    t_3d cylinder_origin = {0.0, 0.0, 0.0};
    t_3d d = {point.x - cylinder_origin.x, point.y - cylinder_origin.y, point.z - cylinder_origin.z};
    t_3d u = {cylinder_axis.x, cylinder_axis.y, cylinder_axis.z};
    double distance = dot(d, u) / dot(u, u);
    t_3d w = {d.x - distance * u.x, d.y - distance * u.y, d.z - distance * u.z};

    // Calculate the surface normal vector at the point
    t_3d axis_direction = {w.x, w.y, 0.0};
    double cos_theta = dot(axis_direction, u) / (sqrt(dot(axis_direction, axis_direction)) * sqrt(dot(u, u)));
    normal->x = axis_direction.x - cos_theta * u.x;
    normal->y = axis_direction.y - cos_theta * u.y;
    normal->z = axis_direction.z - cos_theta * u.z;

    // Normalize the surface normal vector
    double length = sqrt(dot(*normal, *normal));
    normal->x /= length;
    normal->y /= length;
    normal->z /= length;
}

int main() {
    t_3d normal;
    surface_normal(point, &normal);
    printf("Surface normal: (%f, %f, %f)\n", normal.x, normal.y, normal.z);
    return 0;
} */