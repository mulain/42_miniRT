
#include "../incl/minirt.h"

/*
Ray formula:
	r(t) = o + t * d
	Where
		o is the point of the ray
		t is the distance traveled (our target value later)
		d is the defining vector of the ray
Plane formula:
	(p' - p) * n = 0
	Where
		p' is the evaluated point
		p is the point point of the plane
		n is the defining vector of the plane
	Means that the vector connecting p and the evaluated point p'
	is orthogonal to the plane's normvector.
Integrate ray into plane formula instead of p':
	(r(t) - p) * n = 0
	((o + t * d) - p) * n = 0
Solve for t:
	((o + td) - p) * n = 0
	(o + td)n - pn = 0
	on + tdn - pn = 0
	tdn = pn - on
	t = (pn - on) / (dn)
	or
	t = [(p - o) * n] / [d * n] -> used in the function
*/
double	intersect_plane(t_ray ray, t_plane plane)
{
	double		dividend;
	double		divisor;

	dividend = vector_dotprod(point_subtract(plane.point, ray.point),
			plane.vector);
	if (fabs(dividend) < EPSILON)
		return (0);
	divisor = vector_dotprod(plane.vector, ray.vector);
	if (fabs(divisor) < EPSILON)
		return (INFINITY);
	return (dividend / divisor);
}

/*
Sphere formula: ||(p - c)|| = r
	c = center of sphere
	r = radius of sphere
	p = point on sphere
	||x|| means length/magnitude of the vector x

*/
double	intersect_sphere(t_ray ray, t_sphere sphere)
{

}
