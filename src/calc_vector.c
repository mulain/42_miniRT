
#include "../incl/minirt.h"

double	normvector_length(t_normvector vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
