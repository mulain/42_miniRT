
#include "minirt.h"

t_3d	add(t_3d p1, t_3d p2)
{
	return ((t_3d){p1.x + p2.x, p1.y + p2.y, p1.z + p2.z});
}

t_3d	subtract(t_3d p1, t_3d p2)
{
	return ((t_3d){p1.x - p2.x, p1.y - p2.y, p1.z - p2.z});
}

double	distance(t_3d p1, t_3d p2)
{
	double	delta_x;
	double	delta_y;
	double	delta_z;

	delta_x = p2.x - p1.x;
	delta_y = p2.y - p1.y;
	delta_z = p2.z - p1.z;
	return (sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z));
}

t_3d	mult(t_3d v, double mult)
{
	return ((t_3d){v.x * mult, v.y * mult, v.z * mult});
}
