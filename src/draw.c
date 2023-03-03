
#include "../incl/minirt.h"

void	render(t_data *d)
{
	int		x;
	int		y;
	t_ray	ray;

	ray.origin = d->camera.point;
	y = 0;
	while (y < d->height)
	{
		x = 0;
		while (x < d->width)
		{
			ray.direction = get_vector(d, x, y);
			put_pixel(&d->mlx, x, y, trace_ray(d, ray));
			x++;
		}
		printf("\rRendering: %.0f%%", (double)y / (d->height - 1) * 100);
		y++;
	}
	printf("\n");
	mlx_put_image_to_window(d->mlx.mlx, d->mlx.win, d->mlx.img, 0, 0);
}

t_3d	get_vector(t_data *d, int x, int y)
{
	t_3d	looking;
	t_3d	x_axis;
	t_3d	y_axis;
	t_3d	transformed;

	looking.x = (2 * (x + 0.5) / d->width - 1) * d->aspect_ratio * d->fov_ratio;
	looking.y = (1 - 2 * (y + 0.5) / d->height) * d->fov_ratio;
	looking.z = -1;
	looking = subtract(d->camera.point, looking);
	x_axis = /* norm */(cross((t_3d){0, 1, 0}, d->camera.vector));
	y_axis = /* norm */(cross(x_axis, d->camera.vector));
	transformed = add(mult(x_axis, looking.x), d->camera.vector);
	transformed = add(mult(y_axis, looking.y), transformed);
	return (norm(transformed));
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*pxl;

	pxl = mlx->img_addr + (y * mlx->img_line_length + x * mlx->img_bytespp);
	*(unsigned int *)pxl = color;
}

t_intrsct	get_objintersect(t_objlist *objlist, t_ray ray)
{
	t_intrsct	i;
	t_intrsct	i_new;

	i.color.trgb = 0xFF000000;
	i.distance = INFINITY;
	while (objlist)
	{
		i_new = objlist->get_intersection(ray, objlist->object);
		// just calc distance in get_intersection and not point to be faster
		if (i_new.distance < i.distance)
			i = i_new;
		objlist = objlist->next;
	}
	// calc point here only
	return (i);
}

t_color	add_shadow(t_data *d, t_objlist *objlist, t_intrsct i)
{
	t_ray		shadow_ray;
	t_intrsct	new_i;
	double		light_dist;

	light_dist = distance(i.point, d->light.point);
	shadow_ray.direction = norm(subtract(d->light.point, i.point));
	shadow_ray.origin = i.point;
	//shadow_ray.origin = add(i.point, mult(shadow_ray.direction, 0.01));
	while (objlist)
	{
		new_i = objlist->get_intersection(shadow_ray, objlist->object);
		if (new_i.distance - light_dist < EPSILON)
		{
			i.color = adjust_brightness(i.color, 0.1);
			break ;
		}
		objlist = objlist->next;
	}
	return (i.color);
}

int	trace_ray(t_data *d, t_ray ray)
{
	t_intrsct	i;

	i = get_objintersect(d->objectlist, ray);
	i.color = add_shadow(d, d->objectlist, i);
	i.color = add_amblight(i.color, d->amb_light);
	return (i.color.trgb);
}
