
#include "minirt.h"

/*
The length (or magnitude) of a vector is the square root of the dot product
of the vector with itself.
*/
double	length(t_3d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	dot(t_3d v1, t_3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*
The cross product of two vectors is a vector that is perpendicular to
both of the given vectors.
Cross product of parallel vectors is 0.
*/
t_3d	cross(t_3d v1, t_3d v2)
{
	t_3d	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

/*
A normalized vector is of length 1. So divide by its current length
to have a new length of 1.
Multiply to be faster (divison more costly than multiplication)
Care: doesn't guard vs dividing by 0.
*/
t_3d	norm(t_3d v)
{
	double	len;
	double	inv_len;

	len = length(v);
	inv_len = 1 / len;
	v.x *= inv_len;
	v.y *= inv_len;
	v.z *= inv_len;
	return (v);
}
