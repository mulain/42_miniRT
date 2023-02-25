
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
t_intrsct	intersect_plane(t_ray ray, t_plane plane)
{
	double		dividend;
	double		divisor;
	double		result;
	t_intrsct	intersection;

	intersection.color = plane.color.trgb;
	dividend = vector_dotprod(point_subtract(plane.point, ray.point),
			plane.vector);
	divisor = vector_dotprod(plane.vector, ray.vector);
	if (divisor == 0)
		intersection.distance = INFINITY;
	else
	{
		result = dividend / divisor;
		if (result < 0)
			intersection.distance = INFINITY;
		else
			intersection.distance = result;
	}
	return (intersection);
}

double	intersect_plane_old(t_ray ray, t_plane plane)
{
	double		dividend;
	double		divisor;
	double		result;

	dividend = vector_dotprod(point_subtract(plane.point, ray.point),
			plane.vector);
	if (fabs(dividend) < 0)
		return (0);
	divisor = vector_dotprod(plane.vector, ray.vector);
	if (fabs(divisor) < 0)
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
t_intrsct	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vector	oc;
	t_helper	h;
	t_intrsct	intersection;

	intersection.color = sphere.color.trgb;
	oc = point_subtract(ray.point, sphere.point);
	h.a = vector_dotprod(ray.vector, ray.vector);
	h.b = 2 * vector_dotprod(ray.vector, oc);
	h.c = vector_dotprod(oc, oc) - sphere.radius * sphere.radius;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < 0)
		intersection.distance = INFINITY;
	else
		intersection.distance = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	return (intersection);
}

double	intersect_sphere_old(t_ray ray, t_sphere sphere)
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



/*
Infinite cylinder along y axis of radius r has equation
x² + z² - r² = 0.
The equation for a more general cylinder of radius r
oriented along a line p_a + v_a * t:
(q - pa - (va,q - pa)va)2 - r2 = 0
where q = (x,y,z) is a point on the
cylinder.
*/
t_intrsct	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_vector	t;
	t_helper	h;
	double		y_intersect_1;
	double		y_intersect_2;
	double		y_min;
	double		y_max;
	t_intrsct	intersection;

	intersection.color = cylinder.color.trgb;
	t = point_subtract(ray.point, cylinder.point);
	h.a = ray.vector.x * ray.vector.x + ray.vector.z * ray.vector.z;
	h.b = 2 * (t.x * ray.vector.x + t.z * ray.vector.z);
	h.c = t.x * t.x + t.z * t.z - cylinder.radius * cylinder.radius;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < 0)
		return (intersection.distance = INFINITY, intersection);
	h.intersect_1 = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	h.intersect_2 = (-h.b + sqrt(h.discriminant)) / (2 * h.a);
	if (h.intersect_2 < 0)
		return (intersection.distance = INFINITY, intersection);
	y_intersect_1 = ray.point.y + h.intersect_1 * ray.vector.y;
	y_intersect_2 = ray.point.y + h.intersect_2 * ray.vector.y;
	y_min = cylinder.point.y;
	y_max = cylinder.point.y + cylinder.height;
	if ((y_intersect_1 < y_min && y_intersect_2 < y_min)
		|| (y_intersect_1 > y_max && y_intersect_2 > y_max))
		return (intersection.distance = INFINITY, intersection);
	if (y_intersect_1 < y_min)
		h.intersect_1 = (y_min - ray.point.y) / ray.vector.y;
	else if (y_intersect_1 > y_max)
		h.intersect_1 = (y_max - ray.point.y) / ray.vector.y;
	if (y_intersect_2 < y_min)
		h.intersect_2 = (y_min - ray.point.y) / ray.vector.y;
	else if (y_intersect_2 > y_max)
		h.intersect_2 = (y_max - ray.point.y) / ray.vector.y;
	if (h.intersect_1 > h.intersect_2)
		return (intersection.distance = INFINITY, intersection);
	if (h.intersect_1 < 0)
	{
		if (h.intersect_2 < 0)
			return (intersection.distance = INFINITY, intersection);
		return (intersection.distance = h.intersect_2, intersection);
	}
	return (intersection.distance = h.intersect_1, intersection);
}



typedef struct {
    double x, y, z;
} Vec3;

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

typedef struct {
    Vec3 center;
    Vec3 axis;
    double radius;
    double height;
} Cylinder;

double intersectCylinder(Ray ray, Cylinder cylinder) {
    // Transform the ray and cylinder to a common coordinate system
	t_vector	to_cyl;
	t_vector	projction;
	t_vector	to_closestpoint;
	t_vector	to_top;
	t_vector	to_bottom;
	t_vector	intersection;

	double		dotprod;
	double		dist_axis;
	double		dist_surface;
	double		dist_intersct;
	double		dist_top;
	double		dist_bottom;

	t_cylinder	cyl;
	t_ray		ry;


    Vec3 toCylinder = {cylinder.center.x - ray.origin.x, cylinder.center.y - ray.origin.y, cylinder.center.z - ray.origin.z};
	to_cyl = point_subtract(cyl.point, ry.point);
    
	double dotProduct = ray.direction.x * cylinder.axis.x + ray.direction.y * cylinder.axis.y + ray.direction.z * cylinder.axis.z;
    dotprod = vector_dotprod(ry.vector, cyl.vector);

	Vec3 projection = {dotProduct * cylinder.axis.x, dotProduct * cylinder.axis.y, dotProduct * cylinder.axis.z};
    projction = vector_multiply(cyl.vector, dotprod);

	Vec3 toClosestPoint = {toCylinder.x - projection.x, toCylinder.y - projection.y, toCylinder.z - projection.z};
    to_closestpoint = point_subtract(to_cyl, projction);
	
	double distanceToAxis = sqrt(toClosestPoint.x * toClosestPoint.x + toClosestPoint.y * toClosestPoint.y + toClosestPoint.z * toClosestPoint.z);
    dist_axis = vector_length(to_closestpoint);
	
	double distanceToSurface = sqrt(cylinder.radius * cylinder.radius - distanceToAxis * distanceToAxis);
	dist_surface = sqrt(cyl.radius * cyl.radius - dist_axis * dist_axis);

    double distanceToIntersection = dotProduct - distanceToSurface;
	dist_intersct = dotprod - dist_surface;

    Vec3 intersectionPoint = {ray.origin.x + distanceToIntersection * ray.direction.x, ray.origin.y + distanceToIntersection * ray.direction.y, ray.origin.z + distanceToIntersection * ray.direction.z};
    intersection.x = ry.point.x + dist_intersct * ry.vector.x;
	intersection.y = ry.point.y + dist_intersct * ry.vector.y;
	intersection.z = ry.point.z + dist_intersct * ry.vector.z;
	
	Vec3 axisDir = {cylinder.axis.x, cylinder.axis.y, cylinder.axis.z};
	//why?

    Vec3 toTop = {cylinder.center.x + axisDir.x * cylinder.height / 2.0 - intersectionPoint.x,
                  cylinder.center.y + axisDir.y * cylinder.height / 2.0 - intersectionPoint.y,
                  cylinder.center.z + axisDir.z * cylinder.height / 2.0 - intersectionPoint.z};
	to_top.x = cyl.point.x + cyl.vector.x * cyl.height / 2 - intersection.x;
	to_top.y = cyl.point.y + cyl.vector.y * cyl.height / 2 - intersection.y;
	to_top.z = cyl.point.z + cyl.vector.z * cyl.height / 2 - intersection.z;

    Vec3 toBottom = {cylinder.center.x - axisDir.x * cylinder.height / 2.0 - intersectionPoint.x,
                     cylinder.center.y - axisDir.y * cylinder.height / 2.0 - intersectionPoint.y,
                     cylinder.center.z - axisDir.z * cylinder.height / 2.0 - intersectionPoint.z};
	to_bottom.x = cyl.point.x - cyl.vector.x * cyl.height / 2 - intersection.x;
	to_bottom.y = cyl.point.y - cyl.vector.y * cyl.height / 2 - intersection.y;
	to_bottom.z = cyl.point.z - cyl.vector.z * cyl.height / 2 - intersection.z;

    double distanceToTop = sqrt(toTop.x * toTop.x + toTop.y * toTop.y + toTop.z * toTop.z);
	dist_top = vector_length(to_top);
    
	double distanceToBottom = sqrt(toBottom.x * toBottom.x + toBottom.y * toBottom.y + toBottom.z * toBottom.z);
	dist_bottom = vector_length(to_bottom);

    double t = -1;
    if (distanceToIntersection < 0) {
        // The intersection point is behind the ray
        t = -1;
    } else if (distanceToTop < 0 || distanceToBottom < 0 || distanceToTop > cylinder.height || distanceToBottom > cylinder.height) {
        // The ray misses the cylinder
        t = -1;
    } else if (distanceToTop < distanceToBottom) {
        // The ray intersects the top surface of the cylinder
        t = (distanceToTop - toCylinder.y) / ray.direction.y;
    } else {
        // The ray intersects the bottom surface of the cylinder
        t = (distanceToBottom + toCylinder.y) / -ray.direction.y;
    }
    return t;
}
