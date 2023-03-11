
#include "../incl/minirt.h"

double	solve_quad(double a, double b, double c, double *t)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = b * b - 4 * a * c;
	if (discriminant < EPSILON)
		return (INFINITY);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t)
	{
		t[0] = t1;
		t[1] = t2;
	}
	if (t1 < EPSILON)
	{
		if (t2 < EPSILON)
			return (INFINITY);
		return (t2);
	}
	return (t1);
}

t_3d	translate(t_3d obj_axis, t_3d ray_dir)
{
	t_3d	projection;

	projection = scale(obj_axis, dot(obj_axis, ray_dir));
	return (subtract(ray_dir, projection));
}

bool	is_withinbounds(t_3d point, t_3d axis_point, t_3d axis, double height)
{
	double		projection;

	projection = dot(subtract(point, axis_point), axis);
	if (projection > height || projection < EPSILON)
		return (false);
	return (true);
}

double	to_deg(double radians)
{
	return (radians * 180 / M_PI);
}

double	to_rad(double degrees)
{
	return (degrees * M_PI / 180);
}
