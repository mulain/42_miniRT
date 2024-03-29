/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:44:04 by wmardin           #+#    #+#             */
/*   Updated: 2023/03/25 17:44:05 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot(t_3d v1, t_3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*
The cross product of two vectors is a vector that is perpendicular to
both of the given vectors.
Cross product of parallel vectors is 0.
*/
t_3d	cross(t_3d v1, t_3d v2)
{
	t_3d	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

/*
A normalized vector is of length 1. So divide by its current length
to have a new length of 1.
Multiply to be faster (divison costlier than multiplication), prolly
compiler would handle it anyway, but still...)
Care: doesn't guard vs dividing by 0.
*/
t_3d	norm(t_3d v)
{
	double	len;
	double	inv_len;

	len = length(v);
	inv_len = 1 / len;
	v.x *= inv_len;
	v.y *= inv_len;
	v.z *= inv_len;
	return (v);
}

/*
The length (or magnitude) of a vector is the square root of the dot product
of the vector with itself.
*/
double	length(t_3d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	distance(t_3d p1, t_3d p2)
{
	double	delta_x;
	double	delta_y;
	double	delta_z;

	delta_x = p2.x - p1.x;
	delta_y = p2.y - p1.y;
	delta_z = p2.z - p1.z;
	return (sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z));
}
