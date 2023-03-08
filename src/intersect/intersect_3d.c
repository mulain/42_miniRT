
#include "../incl/minirt.h"

t_intrsct	intersect_sphere(t_ray ray, void *obj)
{
	t_sphere	*sphere;
	t_intrsct	i;

	t_3d		l;
	double		tca;
	double		d2;
	double		thc;
	double		t1;
	double		t2;

	sphere = (t_sphere *)obj;
	i.color = sphere->color;
	l = subtract(sphere->center, ray.origin);
	tca = dot(l, ray.direction);
	if (tca < EPSILON)
		return (i.distance = INFINITY, i);
	d2 = dot(l, l) - tca * tca;
	if (d2 - sphere->radius * sphere->radius > EPSILON)
		return (i.distance = INFINITY, i);
	thc = sqrt(sphere->radius * sphere->radius - d2);
	t1 = tca - thc;
	t2 = tca + thc;
	if (t1 < EPSILON)
	{
		if (t2 < EPSILON)
			return (i.distance = INFINITY, i);
		i.distance = t2;
	}
	else
		i.distance = t1;
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	return (i);
}

t_intrsct	intersect_sphere_old(t_ray ray, void *obj)
{
	t_sphere	*sphere;
	t_intrsct	i;
	t_helper	h;

	sphere = (t_sphere *)obj;
	i.color = sphere->color;
	h.oc = subtract(ray.origin, sphere->center);
	h.a = dot(ray.direction, ray.direction);
	h.b = 2 * dot(ray.direction, h.oc);
	h.c = dot(h.oc, h.oc) - sphere->radius * sphere->radius;
	i.distance = solve_quad(h.a, h.b, h.c);
	if (i.distance == INFINITY)
		return (i);
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	return (i);
}

/*
ray_tr is used as an array of 2 doubles.
The direction is actually translated, but ray.origin is not really
a translation of the origin.
*/
t_intrsct	intersect_tube(t_ray ray, void *obj)
{
	t_tube		*tube;
	t_intrsct	i;
	t_helper	h;
	t_ray		ray_tr;
	double		length;

	tube = (t_tube *)obj;
	i.color = tube->color;
	ray_tr.direction = translate(tube->axis, ray.direction);
	ray_tr.origin = translate(tube->axis, subtract(ray.origin, tube->base));
	h.a = dot(ray_tr.direction, ray_tr.direction);
	h.b = 2 * dot(ray_tr.direction, ray_tr.origin);
	h.c = dot(ray_tr.origin, ray_tr.origin) - tube->radius * tube->radius;
	i.distance = solve_quad(h.a, h.b, h.c);
	if (i.distance == INFINITY)
		return (i);
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	length = dot(subtract(i.point, tube->base), tube->axis);
	if (length < EPSILON || length - tube->height > EPSILON)
		i.distance = INFINITY;
	return (i);
}

t_intrsct	intersect_cone(t_ray ray, void *obj)
{
	t_cone		*cone;
	t_intrsct	i;
	t_helper	h;
	t_3d		tr[2];
	double		k;

	cone = (t_cone *)obj;
	i.color = cone->color;
	tr[0] = translate(cone->axis, ray.direction);
	tr[1] = translate(cone->axis, subtract(ray.origin, cone->base));
	k = (cone->radius / cone->height) * (cone->radius / cone->height);
	h.a = tr[0].x * tr[0].x + tr[0].y * tr[0].y - k * tr[0].z * tr[0].z;
	h.b = 2 * (tr[0].x * tr[1].x + tr[0].y * tr[1].y - k * tr[0].z * tr[1].z);
	h.c = tr[1].x * tr[1].x + tr[1].y * tr[1].y - k * tr[1].z * tr[1].z;
	i.distance = solve_quad(h.a, h.b, h.c);
	if (i.distance == INFINITY)
		return (i);
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	return (i);
}

/ Compute the intersection point of a ray and a cone
double intersect_cone(Ray ray, Cone cone) {
    Vector3 axis = normalize(cone.axis);
    Vector3 ba = {cone.base.x - ray.origin.x, cone.base.y - ray.origin.y, cone.base.z - ray.origin.z};
    Vector3 ca = {cone.top.x - ray.origin.x, cone.top.y - ray.origin.y, cone.top.z - ray.origin.z};
    double cos2 = cos(cone.angle) * cos(cone.angle);
    double a = dot(ray.direction, ray.direction) - cos2 * dot(ray.direction, axis) * dot(ray.direction, axis);
    double b = 2 * (dot(ray.direction, ba) - cos2 * dot(ray.direction, axis) * dot(ba, axis));
    double c = dot(ba, ba) - cos2 * dot(ba, axis) * dot(ba, axis);
    double d = b * b - 4 * a * c;
    if (d < 0) {
        return -1;
    }
    double t1 = (-b + sqrt(d)) / (2 * a);
    double t2 = (-b - sqrt(d)) / (2 * a);
    Vector3 p1 = {ray.origin.x + t1 * ray.direction.x, ray.origin.y + t1
	ray.direction.y, ray.origin.z + t1 * ray.direction.z};
Vector3 p2 = {ray.origin.x + t2 * ray.direction.x, ray.origin.y + t2 * ray.direction.y, ray.origin.z + t2 * ray.direction.z};
double height = dot(normalize(ca), p1);
if (height > cone.height || height < 0) {
return -1;
}
if (t1 > 0 && (t2 < 0 || t1 < t2)) {
return t1;
} else if (t2 > 0) {
return t2;
} else {
return -1;
}
}


/* t_intrsct	intersect_cone_fail(t_ray ray, void *obj)
{
	t_cone		*cone;
	t_intrsct	i;
	t_helper	h;
	double		k;

	cone = (t_cone *)obj;
	i.color = cone->color;
	k = (cone->radius / cone->height) * (cone->radius / cone->height);
	h.a = cone->axis.x * cone->axis.x + cone->axis.y * cone->axis.y - k * cone->axis.z * cone->axis.z;
	h.b = 2 * ((ray.origin.x - cone->top.x) * ray.direction.x
			+ (ray.origin.y - cone->top.y) * ray.direction.y
			- k * ((ray.origin.z - cone->top.z) * ray.direction.z));
	h.c = (ray.origin.x - cone->top.x) * (ray.origin.x - cone->top.x)
		+ (ray.origin.y - cone->top.y) * (ray.origin.y - cone->top.y)
		- k * (ray.origin.z - cone->top.z) * (ray.origin.z - cone->top.z);
	i.distance = solve_quad(h.a, h.b, h.c);
	if (i.distance == INFINITY)
		return (i);
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	return (i);
} */
