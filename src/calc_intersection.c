
#include "minirt.h"

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
		p is the point of the plane
		n is the defining vector of the plane
	Means that the vector connecting p and the evaluated point p'
	is orthogonal to the plane's normvector and therefore in the plane.
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
Cases
1)	If dividend is smaller than EPSILON:
	Ray starts in plane -> immediate intersection (return 0)
2)	If divisor is smaller than EPSILON:
	Ray is parallel to plane -> no intersection (return INFINITY)
3)	If result is negative:
	Intersection point is behind ray -> no intersection (return INFINITY)
4)	Intersection found -> one intersection (return dividend / divisor)
*/
double	intersect_plane(t_ray ray, t_plane plane)
{
	double		dividend;
	double		divisor;
	double		result;

	dividend = vector_dotprod(point_subtract(plane.point, ray.point),
			plane.vector);
	if (fabs(dividend) < EPSILON)
		return (0);
	divisor = vector_dotprod(plane.vector, ray.vector);
	if (fabs(divisor) < EPSILON)
		return (INFINITY);
	result = dividend / divisor;
	if (result < 0)
		return (INFINITY);
	return (result);
}

/*
Sphere formula: ||(p - c)||² = r²
	c = center of sphere
	r = radius of sphere
	p = point on sphere
	||x|| means length/magnitude of the vector x
insert ray formula for point p and solve for t to get a
quadratic equation. Solve that to get the discriminants:

if (discriminant < 0)
	return (INFINITY);
	-> no intersection
if (discriminant == 0)
	return (-b / (2 * a));
	-> only one intersection point (tangent)
if (intrsct2 < 0)
	return (INFINITY);
	-> sphere behind ray, no intersection
if (intrsct1 >= 0)
	return (intrsct1);
	-> 2 intersections but we only want intrsct1
	intrsct2 however is also valid (if ray passes thru sphere)
return (intrsct2);
	-> ray originates inside sphere if intrsct1 < 0, one intersection
*/
double	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vector	t;
	t_helper	h;

	t = point_subtract(ray.point, sphere.point);
	h.a = vector_dotprod(ray.vector, ray.vector);
	h.b = 2 * vector_dotprod(ray.vector, t);
	h.c = vector_dotprod(t, t) - sphere.radius * sphere.radius;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < 0)
		return (INFINITY);
	if (h.discriminant == 0)
		return (-h.b / (2 * h.a));
	h.intersect_1 = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	h.intersect_2 = (-h.b + sqrt(h.discriminant)) / (2 * h.a);
	if (h.intersect_2 < 0)
		return (INFINITY);
	if (h.intersect_1 >= 0)
		return (h.intersect_1);
	return (h.intersect_2);
}

double	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	(void)ray;
	(void)cylinder;
	return (INFINITY);
}
