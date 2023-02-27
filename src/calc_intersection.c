
#include "../incl/minirt.h"

t_intrsct	intersect_plane(t_ray ray, t_plane plane)
{
	double		divisor;
	double		result;
	t_intrsct	intersection;

	intersection.color = plane.color.trgb;
	divisor = dot(plane.vector, ray.direction);
	if (fabs(divisor) < EPSILON)
	{
		intersection.distance = INFINITY;
		return (intersection);
	}
	result = dot(subtract(plane.point, ray.origin), plane.vector) / divisor;
	if (result < EPSILON)
		intersection.distance = INFINITY;
	else
		intersection.distance = result;
	return (intersection);
}

t_intrsct	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_3d		oc;
	t_helper	h;
	t_intrsct	intersection;

	intersection.color = sphere.color.trgb;
	oc = subtract(ray.origin, sphere.center);
	h.a = dot(ray.direction, ray.direction);
	h.b = 2 * dot(ray.direction, oc);
	h.c = dot(oc, oc) - sphere.radius * sphere.radius;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < EPSILON)
		intersection.distance = INFINITY;
	else
		intersection.distance = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	return (intersection);
}

double	cylinder_tube(t_ray ray, t_cylinder cylinder)
{
	t_helper	h;
	double		projection;
	t_3d		v;
	t_3d		u;
	t_3d		oc;
	double		t;
	
	// Compute the direction vector of the ray projected onto the cylinder's axis
	projection = dot(ray.direction, cylinder.axis);
	v = mult(cylinder.axis, projection);

	// Compute the direction vector of the ray perpendicular to the cylinder's axis
	v = subtract(ray.direction, v);

	// Compute the origin vector of the ray projected onto the cylinder's axis
	oc = subtract(ray.origin, cylinder.base);
	u = mult(cylinder.axis, dot(oc, cylinder.axis));
	
	// Compute the origin vector of the ray perpendicular to the cylinder's axis
	u = subtract(oc, u);
	
	// Compute coefficients of quadratic equation
	h.a = dot(v, v);
	h.b = 2 * dot(v, u);
	h.c = dot(u, u) - cylinder.radius * cylinder.radius;

	// Solve quadratic equation only for closer point t1
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < 0)
		return (INFINITY);
	h.t1 = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	//h.t2 = (-h.b + sqrt(h.discriminant)) / (2 * h.a);
	if (h.t1 < 0)
		return (INFINITY);
	//Intersection of ray with cylinder is origin of ray + 
		//distance t1 traveled along direction of ray
		t_3d intersection = add(ray.origin, mult(ray.direction, h.t1));
		
		t_3d intersection_relative = subtract(intersection, cylinder.base);
		float intersection_dot_axis = dot(intersection_relative, cylinder.axis);

    
	if (intersection_dot_axis >= -cylinder.height/2 && intersection_dot_axis <= cylinder.height/2)
	{
        t = h.t1;
    }
	else
	{
        // intersection point is outside the valid height range
        return INFINITY;
    }

    // check if the intersection point is in front of the ray origin
    if (t < 0) {
        // intersection point is behind the ray origin
        return INFINITY;
    }
	else
	{
        return t;
    }
	return t;

	

}

t_intrsct	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_intrsct	i;
	/* t_3d		u;
	t_3d		v;
	t_3d		oc;
	double		projection;
	double		t;
	t_helper	h;
	t_plane		cap_plane;
	t_3d		cap_intersct; */

	i.color = cylinder.color.trgb;
	i.distance = cylinder_tube(ray, cylinder);
	
	return i;
	
	
/* 	
	
	cap_plane.point = cylinder.base;
	cap_plane.vector = cylinder.axis;
	 */




/* 	h.t_base = intersect_plane(ray, cap_plane).distance;
	cap_intersct = add(ray.origin, mult(ray.direction, h.t_base));
	if (distance(cap_intersct, cylinder.base) > cylinder.radius)
		h.t_base = INFINITY;
	cap_plane.point = cylinder.top;
	h.t_top = intersect_plane(ray, cap_plane).distance;
	cap_intersct = add(ray.origin, mult(ray.direction, h.t_top));
	if (distance(cap_intersct, cylinder.top) > cylinder.radius)
		h.t_top = INFINITY; */
/* 
	// Have to check for intersection with both caps, can't easily determine
	// which one will be hit.
	projection = dot(ray.direction, cylinder.axis);
	oc = subtract(cylinder.base, ray.origin);

	t = dot(oc, cylinder.axis) / projection;
	//double t = ((circle.center.x - ray.start.x) * circle.normal.x + (circle.center.y - ray.start.y) * circle.normal.y + (circle.center.z - ray.start.z) * circle.normal.z) / dot_product;
	// if (t < 0) no cap intersetion (is behind starting point)
	t_3d intersection_point = add(ray.origin, mult(ray.direction, t));
	double dist = distance(intersection_point, cylinder.base);
	if (dist < cylinder.radius)
		return (i.distance = dist, i); */


	




}

/* t_intrsct	intersect_cylinder_no_Y(t_ray ray, t_cylinder cylinder)
{
	t_3d		oc;
	t_helper	h;
	double		y_t1;
	double		y_t2;
	double		y_min;
	double		y_max;
	t_intrsct	intersection;

	intersection.color = cylinder.color.trgb;
	oc = subtract(ray.origin, cylinder.base);
	h.a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	h.b = 2 * (oc.x * ray.direction.x + oc.z * ray.direction.z);
	h.c = oc.x * oc.x + oc.z * oc.z - cylinder.radius * cylinder.radius;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < 0)
		return (intersection.distance = INFINITY, intersection);
	h.t1 = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	h.t2 = (-h.b + sqrt(h.discriminant)) / (2 * h.a);
	if (h.t2 < 0)
		return (intersection.distance = INFINITY, intersection);
	y_t1 = ray.origin.y + h.t1 * ray.direction.y;
	y_t2 = ray.origin.y + h.t2 * ray.direction.y;
	y_min = cylinder.base.y;
	y_max = cylinder.base.y + cylinder.height;
	if ((y_t1 < y_min && y_t2 < y_min)
		|| (y_t1 > y_max && y_t2 > y_max))
		return (intersection.distance = INFINITY, intersection);
	if (y_t1 < y_min)
		h.t1 = (y_min - ray.origin.y) / ray.direction.y;
	else if (y_t1 > y_max)
		h.t1 = (y_max - ray.origin.y) / ray.direction.y;
	if (y_t2 < y_min)
		h.t2 = (y_min - ray.origin.y) / ray.direction.y;
	else if (y_t2 > y_max)
		h.t2 = (y_max - ray.origin.y) / ray.direction.y;
	if (h.t1 > h.t2)
		return (intersection.distance = INFINITY, intersection);
	if (h.t1 < 0)
	{
		if (h.t2 < 0)
			return (intersection.distance = INFINITY, intersection);
		return (intersection.distance = h.t2, intersection);
	}
	return (intersection.distance = h.t1, intersection);
}
 */