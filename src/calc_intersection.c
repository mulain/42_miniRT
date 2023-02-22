
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
double	intersect_plane(t_ray ray, void *content)
{
	t_plane		*plane;
	double		dividend;
	double		divisor;
	double		result;

	plane = (t_plane *)content;
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
double	intersect_sphere(t_ray ray, void *content)
{
	t_vector	t;
	t_helper	h;
	t_sphere	*sphere;

	sphere = (t_plane *)content;
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

/*
Infinite cylinder along y axis of radius r has equation
x² + z² - r² = 0.
The equation for a more general cylinder of radius r
oriented along a line p_a + v_a * t:
(q - pa - (va,q - pa)va)2 - r2 = 0
where q = (x,y,z) is a point on the
cylinder.
*/
double	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_vector	t;
	t_helper	h;
	double		y_intersect_1;
	double		y_intersect_2;
	double		y_min;
	double		y_max;


	t = point_subtract(ray.point, cylinder.point);
	h.a = ray.vector.x * ray.vector.x + ray.vector.z * ray.vector.z;
	h.b = 2 * (t.x * ray.vector.x + t.z * ray.vector.z);
	h.c = t.x * t.x + t.z * t.z - cylinder.radius * cylinder.radius;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < 0)
		return (INFINITY); //no intersection
	h.intersect_1 = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	h.intersect_2 = (-h.b + sqrt(h.discriminant)) / (2 * h.a);
	if (h.intersect_2 < 0)
		return (INFINITY);
	y_intersect_1 = ray.point.y + h.intersect_1 * ray.vector.y;
	y_intersect_2 = ray.point.y + h.intersect_2 * ray.vector.y;
	y_min = cylinder.point.y;
	y_max = cylinder.point.y + cylinder.height;
	if ((y_intersect_1 < y_min && y_intersect_2 < y_min)
		|| (y_intersect_1 > y_max && y_intersect_2 > y_max))
		return (INFINITY);
	if (y_intersect_1 < y_min)
		h.intersect_1 = (y_min - ray.point.y) / ray.vector.y;
	else if (y_intersect_1 > y_max)
		h.intersect_1 = (y_max - ray.point.y) / ray.vector.y;
	if (y_intersect_2 < y_min)
		h.intersect_2 = (y_min - ray.point.y) / ray.vector.y;
	else if (y_intersect_2 > y_max)
		h.intersect_2 = (y_max - ray.point.y) / ray.vector.y;
	if (h.intersect_1 > h.intersect_2)
		return (INFINITY);
	if (h.intersect_1 < 0)
	{
		if (h.intersect_2 < 0)
			return (INFINITY);
		return (h.intersect_2);
	}
	return (h.intersect_1);
}
