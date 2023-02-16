
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

	print_point(ray.point, "ray point");
	print_point(plane.point, "plane point");
	print_vector(point_subtract(plane.point, ray.point), "plane - point");

	dividend = vector_dotprod(point_subtract(plane.point, ray.point),
			plane.vector);
	printf("dividend:%f\n", dividend);
	
	divisor = vector_dotprod(plane.vector, ray.vector);
	printf("divisor:%f\n", divisor);
	
	
	
	if (fabs(dividend) < EPSILON)
		return (0);
	
	if (fabs(divisor) < EPSILON)
		return (INFINITY);
	return (dividend / divisor);
}
