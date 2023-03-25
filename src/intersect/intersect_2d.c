/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:46:46 by wmardin           #+#    #+#             */
/*   Updated: 2023/03/25 17:46:47 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	i.point = add(ray.origin, scale(ray.direction, i.distance));
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

t_intrsct	intersect_triangle(t_ray ray, void *obj)
{
	t_triangle	*triangle;
	t_intrsct	i;
	t_plane		tri_plane;

	triangle = (t_triangle *)obj;
	tri_plane = (t_plane){triangle->v1, triangle->vector, triangle->color};
	i = intersect_plane(ray, &tri_plane);
	if (i.distance == INFINITY)
		return (i);
	if (!is_left(i.point, triangle->vector, triangle->v1, triangle->v2)
		|| !is_left(i.point, triangle->vector, triangle->v2, triangle->v3)
		|| !is_left(i.point, triangle->vector, triangle->v3, triangle->v1))
		return (i.distance = INFINITY, i);
	return (i);
}

bool	is_left(t_3d point, t_3d normal, t_3d vertex1, t_3d vertex2)
{
	t_3d	side;
	t_3d	to_point;

	side = subtract(vertex2, vertex1);
	to_point = subtract(point, vertex1);
	if (dot(normal, cross(side, to_point)) < EPSILON)
		return (false);
	return (true);
}
