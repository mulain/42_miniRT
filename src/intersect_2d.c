
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
	if (distance(i.point, disc->center) > disc->radius)
		i.distance = INFINITY;
	return (i);
}

/* t_intrsct intersect_triangle(t_ray ray, void *obj)
{
	t_triangle	*triangle;
	t_intrsct	i;
	t_3d		vector;

	triangle = (t_triangle *)obj;
	i.color = triangle->color;


} */
/* 

double	trinagle_intersection(t_p3 d, t_p3 cam_o, t_triangle tri)
{
	t_p3	tri_norm;
	double	plane_inter;
	t_p3	inter_p;

	tri_norm = calculate_triangle_normal(tri);
	plane_inter = plane_intersection(d, cam_o, tri_norm, tri.p1);
	inter_p = _add(cam_o, _multy(d, plane_inter));
	if (!check_p_in_borders(tri.p1, tri.p2, tri.p3, inter_p))
		return (INFINITY);
	if (!check_p_in_borders(tri.p3, tri.p1, tri.p2, inter_p))
		return (INFINITY);
	if (!check_p_in_borders(tri.p2, tri.p3, tri.p1, inter_p))
		return (INFINITY);
	return (plane_inter);
}


bool	check_p_in_borders(t_p3 p1, t_p3 p2, t_p3 p3, t_p3 inter_p)
{
	t_p3	v1;
	t_p3	v2;
	t_p3	v3;
	t_p3	cross1;
	t_p3	cross2;

	v1 = _substruct(p2, p1);
	v2 = _substruct(p3, p1);
	v3 = _substruct(inter_p, p1);
	cross1 = _cross(v1, v2);
	cross2 = _cross(v1, v3);
	if (_dot(cross1, cross2) / _lenth(cross1) * _lenth(cross2) < 0)
		return (false);
	return (true);
} */