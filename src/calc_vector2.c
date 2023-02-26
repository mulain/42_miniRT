
#include "minirt.h"

/*
The length (or magnitude) of a vector is the square root of the dot product
of the vector with itself.
*/
double	length(t_3d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
Algebraically, the dot product is the sum of the products of the
corresponding entries of the two vectors.
(used this in the function)

Geometrically, it is the product of the Euclidean magnitudes of
the two vectors and the cosine of the angle between them.
A·B = ||A|| ||B|| cos(θ)
where ||A|| and ||B|| are the magnitudes of the vectors,
and θ is the angle between the vectors.

These definitions are equivalent when using Cartesian point.

Cosine in rel. to angle between vectors:
	-	0 deg: cosine is 1
	-	180 deg: cosine is -1
	-	90 deg: cosine is 0

Dotprod depends on angle (deg) between vectors:
	> 0 && < 90		positive
	== 90			0
	> 90 && < 180	negative
*/
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
