/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:46:12 by wmardin           #+#    #+#             */
/*   Updated: 2023/03/25 17:49:21 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minirt.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*pxl;

	pxl = mlx->img_addr + (y * mlx->img_line_length + x * mlx->img_bytespp);
	*(unsigned int *)pxl = color;
}

bool	is_shadowed(t_3d light_origin, t_objlst *objnode, t_3d point)
{
	t_ray		shadow_ray;
	double		light_dist;
	double		block_dist;

	light_dist = distance(point, light_origin);
	shadow_ray.direction = norm(subtract(light_origin, point));
	shadow_ray.origin = point;
	while (objnode)
	{
		block_dist = objnode->get_intersection(shadow_ray,
				objnode->object).distance;
		if (block_dist < light_dist)
			return (true);
		objnode = objnode->next;
	}
	return (false);
}

double	cosfactor(t_3d ray_origin, t_3d hitpoint, t_3d surface_normal)
{
	t_3d	to_light;
	double	cosine_factor;

	to_light = norm(subtract(hitpoint, ray_origin));
	cosine_factor = dot(surface_normal, to_light) * -1;
	if (cosine_factor < EPSILON)
		return (0);
	return (cosine_factor);
}

/*
R = I - 2(I · N)N
R = 2(N · L)N - L
return (subtract(scale(normal, 2 * dotprod), incoming));
*/
t_3d	reflect(t_3d incoming, t_3d normal)
{
	double		dotprod;

	dotprod = dot(incoming, normal);
	return (subtract(incoming, scale(normal, 2 * dotprod)));
}
