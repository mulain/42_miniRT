
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
Sphere formula: square(||(p - c)||) = r * r
	c = center of sphere
	r = radius of sphere
	p = point on sphere
	||x|| means length/magnitude of the vector x

*/
double	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vector	t;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		intrsct1;
	double		intrsct2;

	t = point_subtract(ray.point, sphere.point);
	a = vector_dotprod(ray.vector, ray.vector);
	b = 2 * vector_dotprod(ray.vector, t);
	c = vector_dotprod(t, t) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (INFINITY); // no intersection
	if (discriminant == 0)
		return (-b / (2 * a)); //only one intersection point
	intrsct1 = (-b - sqrt(discriminant)) / (2 * a);
	intrsct2 = (-b + sqrt(discriminant)) / (2 * a);
	if (intrsct2 < 0)
		return (INFINITY); //sphere behind ray
	if (intrsct1 >= 0)
		return (intrsct1);
		// 2 intersections but we only want intrsct1
		// intrsct2 however is also valid (if ray passes thru sphere)
	return (intrsct2); // ray originates inside sphere
}
