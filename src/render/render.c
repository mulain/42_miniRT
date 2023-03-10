
#include "../incl/minirt.h"

void	*render(void *ptr)
{
	t_data		*d;
	int			id;
	int			x;
	int			y;
	int			job;
	t_ray		ray;

	d = ((t_threadinfo *)ptr)->data;
	id = ((t_threadinfo *)ptr)->id;
	ray.origin = d->camera.point;
	job = d->height / THREADCOUNT;
	y = id * job;
	while (y < job * (id + 1))
	{
		x = 0;
		while (x < d->width)
		{
			ray.direction = get_vector(d, x, y);
			put_pixel(&d->mlx, x, y, trace_ray(d, d->lightlst, ray));
			x++;
		}
		if (id == THREADCOUNT - 1)
			printf("\rRendering: %.1f", (float)100 * (y / THREADCOUNT) / job);
		y++;
	}
	if (id == THREADCOUNT - 1)
		printf("\rRendering: 100.0%%\n");
	return (NULL);
}

t_3d	get_vector(t_data *d, int x, int y)
{
	t_3d	looking;
	t_3d	transformed;

	looking.x = (2 * (x + 0.5) / d->width - 1) * d->aspect_ratio * d->fov_ratio;
	looking.y = (1 - 2 * (y + 0.5) / d->height) * d->fov_ratio;
	looking.z = -1;
	// looking = subtract(d->camera.point, looking);
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

bool	is_shadowed(t_light *light, t_objlst *objnode, t_3d point)
{
	t_ray		shadow_ray;
	double		light_dist;
	double		block_dist;

	light_dist = distance(point, light->origin);
	shadow_ray.direction = norm(subtract(light->origin, point));
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
