/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:46:08 by wmardin           #+#    #+#             */
/*   Updated: 2023/08/07 16:20:01 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minirt.h"

/*
if (h.id == THREADCOUNT - 1)
	{
		printf(STATUSMSG, 100 * (float)(h.y % h.job) / (float)h.job);
		fflush(stdout);
	}
*/
void	*render_threads(void *ptr)
{
	t_data		*d;
	t_inthelp	h;
	t_ray		ray;

	d = ((t_threadinfo *)ptr)->data;
	h.id = ((t_threadinfo *)ptr)->id;
	ray.origin = d->camera.point;
	h.job = d->height / THREADCOUNT;
	h.y = h.id * h.job;
	while (h.y < h.job * (h.id + 1))
	{
		h.x = 0;
		while (h.x < d->width)
		{
			ray.direction = get_vector(d, h.x, h.y);
			put_pixel(&d->mlx, h.x, h.y, trace_ray(d, ray, 0));
			h.x++;
		}
		if (h.id == THREADCOUNT - 1)
			printf(STATUSMSG, 100 * (float)(h.y % h.job) / (float)h.job);
		h.y++;
	}
	if (h.id == THREADCOUNT - 1)
		printf(STATUSDONE);
	return (NULL);
}

void	render(t_data *d)
{
	int			x;
	int			y;
	t_ray		ray;

	ray.origin = d->camera.point;
	y = 0;
	while (y < d->height)
	{
		x = 0;
		while (x < d->width)
		{
			ray.direction = get_vector(d, x, y);
			put_pixel(&d->mlx, x, y, trace_ray(d, ray, 0));
			x++;
		}
		printf(STATUSMSG, 100 * ((float)y / d->height));
		y++;
	}
	printf(STATUSDONE);
}

t_3d	get_vector(t_data *d, int x, int y)
{
	t_3d	looking;
	t_3d	transformed;

	looking.x = (2 * (x + 0.5) / d->width - 1) * d->aspect_ratio * d->fov_ratio;
	looking.y = (1 - 2 * (y + 0.5) / d->height) * d->fov_ratio;
	looking.z = -1;
	transformed = add(scale(d->camera.x_axis, looking.x), d->camera.vector);
	transformed = add(scale(d->camera.y_axis, looking.y), transformed);
	return (norm(transformed));
}

int	trace_ray(t_data *d, t_ray ray, int depth)
{
	t_intrsct	i;

	i = get_objintersect(d->objectlist, ray);
	if (!i.objnode)
		return (0x00000000);
	i.depth = depth;
	i.ray = ray;
	i.coeff = (t_rgb){0, 0, 0};
	i.amb = ambient_component(d, i);
	i.diff = diffuse_component(d, i, d->lightlst);
	i.spec = specular_component(d, i, d->lightlst);
	return (add_colors(i.amb, i.diff, i.spec));
}

t_intrsct	get_objintersect(t_objlst *objnode, t_ray ray)
{
	t_intrsct	i;
	t_intrsct	i_new;

	i.distance = INFINITY;
	i.objnode = NULL;
	while (objnode)
	{
		i_new = objnode->get_intersection(ray, objnode->object);
		if (i_new.distance < i.distance)
		{
			i = i_new;
			i.objnode = objnode;
		}
		objnode = objnode->next;
	}
	return (i);
}
