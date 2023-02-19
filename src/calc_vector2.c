
#include "minirt.h"

/*
The length (or magnitude) of a vector is the square root of the dot product
of the vector with itself.
*/
double	vector_length(t_vector v)
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
double	vector_dotprod(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*
The cross product of two vectors is a vector that is perpendicular to
both of the given vectors.
Cross product of parallel vectors is 0.
*/
t_vector	vector_crossprod(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

/*
A normalized vector is of length 1. So divide by its current length
to have a new length of 1.
*/
t_vector	vector_normalize(t_vector v)
{
	return (vector_divide(v, vector_length(v)));
}
