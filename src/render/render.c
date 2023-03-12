
#include "../incl/minirt.h"

void	*render(void *ptr)
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
			put_pixel(&d->mlx, h.x, h.y, trace_ray(d, d->lightlst, ray));
			h.x++;
		}
		if (h.id == THREADCOUNT - 1)
			printf(STATUSMSG, (float)100 * (h.y / THREADCOUNT) / h.job);
		h.y++;
	}
	if (h.id == THREADCOUNT - 1)
		printf(STATUSDONE);
	return (NULL);
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

int	trace_ray(t_data *d, t_lightlst *lightnode, t_ray ray)
{
	t_intrsct	i;
	t_rgb		coeff;
	//int		color;

	i = get_objintersect(d->objectlist, ray);
	if (!i.objnode) // no intersection, return bckgcolor
		return (0x00000000);
	coeff = (t_rgb){0, 0, 0};
	add_lighttocoeff(&coeff, d->amb_light.color, d->amb_light.brightness);
	while (lightnode)
	{
		if (!is_shadowed(lightnode->light, d->objectlist, i.point))
			add_lighttocoeff(&coeff, lightnode->light->color, bright_diffuse(*lightnode->light, i));
		lightnode = lightnode->next;
	}
	i.color.trgb = apply_coeff(i.color, coeff);
	return (i.color.trgb);
}

t_intrsct	get_objintersect(t_objlst *objnode, t_ray ray)
{
	t_intrsct	i;
	t_intrsct	i_new;

	i.color.trgb = 0xFF000000;
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
