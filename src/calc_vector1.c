
#include "../incl/minirt.h"

t_vector	point_add(t_point p1, t_point p2)
{
	return ((t_vector){p1.x + p2.x, p1.y + p2.y, p1.z + p2.z});
}

t_vector	point_subtract(t_point p1, t_point p2)
{
	return ((t_vector){p1.x - p2.x, p1.y - p2.y, p1.z - p2.z});
}

t_vector	vector_multiply(t_vector v, double mult)
{
	return ((t_vector){v.x * mult, v.y * mult, v.z * mult});
}

t_vector	vector_divide(t_vector v, double div)
{
	return ((t_vector){v.x / div, v.y / div, v.z / div});
}
