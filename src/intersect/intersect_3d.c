
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
	i.point = add(ray.origin, scale(ray.direction, i.distance));
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
	i.point = add(ray.origin, scale(ray.direction, i.distance));
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
	i.point = add(ray.origin, scale(ray.direction, i.distance));
	length = dot(subtract(i.point, tube->base), tube->axis);
	if (length < EPSILON || length - tube->height > EPSILON)
		i.distance = INFINITY;
	return (i);
}

t_intrsct	intersect_cone_leessold(t_ray ray, void *obj)
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
	i.point = add(ray.origin, scale(ray.direction, i.distance));
	return (i);
}


/* a = k * d dot d - (d dot n)²
b = 2 * (k * (d dot e) - (d dot n) * (e dot n - c dot n))
c = k * (e dot e - 2 * (e dot c) + c dot c) - (e dot n - c dot n)² */
t_intrsct	intersect_cone(t_ray ray, void *obj)
{
	t_cone		*cone;
	t_intrsct	i;
	t_helper	h;
	//double		projection;
	t_3d		co;

	cone = (t_cone *)obj;
	i.color = cone->color;
	co = subtract(ray.origin, cone->apex);
	h.a = dot(ray.direction, cone->axis) * dot(ray.direction, cone->axis) - cos(cone->theta_rad) * cos(cone->theta_rad);
	h.b = 2 * (dot(ray.direction, cone->axis) * dot(co, cone->axis) - dot(ray.direction, co) * cone->theta_deg * cone->theta_deg);
	h.c = dot(co, cone->axis) * dot(co, cone->axis) - dot(co, co) * cone->theta_deg * cone->theta_deg;
	i.distance = solve_quad(h.a, h.b, h.c);
   if (i.distance == INFINITY)
		return (i);
	/* projection = dot(subtract(i.point, cone->apex), cone->axis);
	if (projection > cone->height || projection < EPSILON)
		i.distance = INFINITY;
	else */
		i.point = add(ray.origin, scale(ray.direction, i.distance));
	return (i);
}

t_intrsct	intersect_cone__(t_ray ray, void *obj)
{
	t_cone		*cone;
	t_intrsct	i;
	t_helper	h;
	//t_3d		tr[2];
	double		m;
	t_3d		w;
	double		dot_vh;
	double		dot_vw;
	//double		dist;

	cone = (t_cone *)obj;
	i.color = cone->color;
	m = (cone->radius * cone->radius) / (cone->height * cone->height);
	w = subtract(ray.origin, cone->apex);
	dot_vh = dot(ray.direction, cone->axis);
	dot_vw = dot(ray.direction, w);
	h.a = dot(ray.direction, ray.direction) - m * dot_vh * dot_vh - dot_vh * dot_vh;
	h.b = 2 * (dot_vw - m * dot_vh * dot(w, cone->axis) - dot_vh * dot(w, cone->axis));
	h.c = dot(w, w) - m * dot(w, cone->axis) * dot(w, cone->axis) - dot(w, cone->axis) * dot(w, cone->axis);
	i.distance = solve_quad(h.a, h.b, h.c);
	if (i.distance == INFINITY)
		return (i);
	double projection = dot(subtract(i.point, cone->base), cone->axis);
	if (projection > cone->height || projection < EPSILON)
		i.distance = INFINITY;
	else
		i.point = add(ray.origin, scale(ray.direction, i.distance));
	return (i);
}

t_intrsct	intersect_cone_chatgpt(t_ray ray, void *obj)
{
    
	t_cone		*cone;
	t_intrsct	i;
	cone = (t_cone *)obj;
	i.color = cone->color;

// Translate ray origin and cone base to cone local coordinates
	 t_3d l_origin = subtract(ray.origin, cone->base);
    t_3d l_axis = norm(cone->axis);
    t_3d l_direction = norm(ray.direction);
    // Compute coefficients of quadratic equation
    double a = dot(l_direction, l_direction) - (1 + cone->radius * cone->radius / (cone->height * cone->height)) * dot(l_direction, l_axis) * dot(l_direction, l_axis);
    double b = 2 * (dot(l_direction, l_origin) - (1 + cone->radius * cone->radius / (cone->height * cone->height)) * dot(l_direction, l_axis) * dot(l_origin, l_axis));
    double c = dot(l_origin, l_origin) - (1 + cone->radius * cone->radius / (cone->height * cone->height)) * dot(l_origin, l_axis) * dot(l_origin, l_axis);
    i.distance = solve_quad(a, b, c);
   if (i.distance == INFINITY)
		return (i);
	double projection = dot(subtract(i.point, cone->base), cone->axis);
	if (projection > cone->height || projection < EPSILON)
		i.distance = INFINITY;
	else
		i.point = add(ray.origin, scale(ray.direction, i.distance));
	return (i);
}
