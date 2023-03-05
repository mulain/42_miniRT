
#include "../incl/minirt.h"

t_vector	point_add(t_vector p1, t_vector p2)
{
	return ((t_vector){p1.x + p2.x, p1.y + p2.y, p1.z + p2.z});
}

t_vector	point_subtract(t_vector p1, t_vector p2)
{
	return ((t_vector){p1.x - p2.x, p1.y - p2.y, p1.z - p2.z});
}

double	point_distance(t_vector p1, t_vector p2)
{
	double	delta_x;
	double	delta_y;
	double	delta_z;

	delta_x = p2.x - p1.x;
	delta_y = p2.y - p1.y;
	delta_z = p2.z - p1.z;
	return (sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z));
}

t_vector	vector_multiply(t_vector v, double mult)
{
	return ((t_vector){v.x * mult, v.y * mult, v.z * mult});
}

t_vector	vector_divide(t_vector v, double div)
{
	return ((t_vector){v.x / div, v.y / div, v.z / div});
}
