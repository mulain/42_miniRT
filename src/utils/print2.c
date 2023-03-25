/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:44:15 by wmardin           #+#    #+#             */
/*   Updated: 2023/03/25 17:44:17 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_sphere(t_sphere *sphere)
{
	printf("----- Sphere -----\n");
	printf("Center:\n");
	printf("  x: %f\n", sphere->center.x);
	printf("  y: %f\n", sphere->center.y);
	printf("  z: %f\n", sphere->center.z);
	printf("Radius:\n");
	printf("  %f\n", sphere->radius);
	printf("Color:\n");
	printf("  r: %i\n", sphere->color.r);
	printf("  g: %i\n", sphere->color.g);
	printf("  b: %i\n", sphere->color.b);
}

void	print_plane(t_plane *plane)
{
	printf("----- Plane -----\n");
	printf("Point:\n");
	printf("  x: %f\n", plane->point.x);
	printf("  y: %f\n", plane->point.y);
	printf("  z: %f\n", plane->point.z);
	printf("Vector:\n");
	printf("  x: %f\n", plane->vector.x);
	printf("  y: %f\n", plane->vector.y);
	printf("  z: %f\n", plane->vector.z);
	printf("Color:\n");
	printf("  r: %i\n", plane->color.r);
	printf("  g: %i\n", plane->color.g);
	printf("  b: %i\n", plane->color.b);
}

void	print_tube(t_tube *tube)
{
	printf("----- tube -----\n");
	printf("Base:\n");
	printf("  x: %f\n", tube->base.x);
	printf("  y: %f\n", tube->base.y);
	printf("  z: %f\n", tube->base.z);
	printf("Axis:\n");
	printf("  x: %f\n", tube->axis.x);
	printf("  y: %f\n", tube->axis.y);
	printf("  z: %f\n", tube->axis.z);
	printf("Radius:\n");
	printf("  %f\n", tube->radius);
	printf("Height:\n");
	printf("  %f\n", tube->height);
	printf("Color:\n");
	printf("  r: %i\n", tube->color.r);
	printf("  g: %i\n", tube->color.g);
	printf("  b: %i\n", tube->color.b);
}

void	print_3d(t_3d v, char *name)
{
	if (name)
		printf("Name: %s\n", name);
	else
		printf("Vector:\n");
	printf("  x: %f\n", v.x);
	printf("  y: %f\n", v.y);
	printf("  z: %f\n", v.z);
}
