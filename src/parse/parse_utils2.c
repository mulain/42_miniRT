
#include "../incl/minirt.h"

t_phong	parse_phong(t_data *d, char *input, char *msg)
{
	t_3d		temp;
	//double		sum;

	temp = parse_point(d, input, msg);
	if (temp.x < 0 || temp.x > 1.0
		|| temp.y < 0 || temp.y > 1.0
		|| temp.z < 0 || temp.z > 1.0)
		error_exit(d, msg);
	/* sum = temp.x + temp.y + temp.z;
	temp.x *= temp.x / sum;
	temp.y *= temp.y / sum;
	temp.z *= temp.z / sum; */
	return ((t_phong){temp.x, temp.y, temp.z});
}
