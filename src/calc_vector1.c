
#include "../incl/minirt.h"

t_vector	vector_add(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vector	vector_subtract(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vector	vector_multiply(t_vector v, double mult)
{
	return ((t_vector){v.x * mult, v.y * mult, v.z * mult});
}

t_vector	vector_divide(t_vector v, double div)
{
	return ((t_vector){v.x / div, v.y / div, v.z / div});
}
