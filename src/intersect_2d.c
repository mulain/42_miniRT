
#include "../incl/minirt.h"

t_intrsct	intersect_plane(t_ray ray, void *obj)
{
	t_plane		*plane;
	t_intrsct	i;
	double		div;

	plane = (t_plane *)obj;
	i.color = plane->color;
	div = dot(plane->vector, ray.direction);
	if (fabs(div) < EPSILON)
		return (i.distance = INFINITY, i);
	i.distance = dot(subtract(plane->point, ray.origin), plane->vector) / div;
	if (i.distance < EPSILON)
		return (i.distance = INFINITY, i);
	i.point = add(ray.origin, mult(ray.direction, i.distance));
	return (i);
}

t_intrsct	intersect_disc(t_ray ray, void *obj)
{
	t_disc		*disc;
	t_intrsct	i;
	t_plane		disc_plane;

	disc = (t_disc *)obj;
	disc_plane.point = disc->center;
	disc_plane.vector = disc->vector;
	disc_plane.color = disc->color;
	i = intersect_plane(ray, &disc_plane);
	if (i.distance == INFINITY)
		return (i);
	if (distance(i.point, disc->center) > disc->radius)
		i.distance = INFINITY;
	return (i);
}

t_intrsct intersect_triangle(t_ray ray, void *obj)
{
	t_triangle	*triangle;
	t_intrsct	i;
	t_plane		tri_plane;

	triangle = (t_triangle *)obj;
	tri_plane.color = triangle->color;
	tri_plane.point = triangle->p1;
	tri_plane.vector = triangle->vector;
	i = intersect_plane(ray, &tri_plane);
	if (i.distance == INFINITY)
		return (i);
	if (!is_inside(triangle->p1, triangle->p2, triangle->p3, i.point))
		return (i.distance = INFINITY, i);
	if (!is_inside(triangle->p3, triangle->p1, triangle->p2, i.point))
		return (i.distance = INFINITY, i);
	if (!is_inside(triangle->p2, triangle->p3, triangle->p1, i.point))
		return (i.distance = INFINITY, i);
	return (i);
}

bool	is_inside(t_3d p1, t_3d p2, t_3d p3, t_3d p_eval)
{
	t_3d	v1;
	t_3d	v2;
	t_3d	v3;
	t_3d	cross1;
	t_3d	cross2;

	v1 = subtract(p2, p1);
	v2 = subtract(p3, p1);
	v3 = subtract(p_eval, p1);
	cross1  = cross(v1, v2);
	cross2 = cross(v1, v3);
	if (dot(cross1, cross2)/*  / length(cross1) * length(cross2) */ < 0)
		return (false);
	return (true);
}
