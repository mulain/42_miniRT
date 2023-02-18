// # include "vectormath.h"
// # include "minirt.h"
# include "../incl/minirt.h"

double	sqr(double n)
{
	return (n * n);
}

double	length_base(t_vector vec)
{
	return (sqr(vec.x) + sqr(vec.y) + sqr(vec.z));
}

double	length_sqr(t_vector vec)
{
	return (sqr(length_base(vec)));
}

double	dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	cross(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

t_vector	sum(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;

	return (ret);
}

t_vector	extr(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

t_vector	mult(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;
	ret.z = v1.z * v2.z;
	return (ret);
}

t_vector	divide(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.x / v2.x;
	ret.y = v1.y / v2.y;
	ret.z = v1.z / v2.z;
	return (ret);
}

t_vector	negative(t_vector v1)
{
	t_vector	ret;

	ret.x = -v1.x;
	ret.y = -v1.y;
	ret.z = -v1.z;
	return (ret);
}

void	equalize(t_vector *v1, t_vector v2)
{
	v1->x = v2.x;
	v1->y = v2.y;
	v1->z = v2.z;
}





