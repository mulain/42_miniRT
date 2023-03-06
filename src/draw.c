
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
		printf("\rRendering: %.1f%%", (double)y / (d->height - 1) * 100);
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


int	trace_ray(t_data *d, t_ray ray)
{
	t_intrsct	i;
	t_rgb		rgb_coeff;

	i = get_objintersect(d->objectlist, ray);
	if (!i.objnode) // no intersection, return bckgcolor
		return (0x00000000);
	rgb_coeff = add_lightcoeff((t_rgb){0, 0, 0}, d->amb_light.color, d->amb_light.brightness);
	if (!is_shadowed(d, d->objectlist, i.point))
	{
		rgb_coeff = add_lightcoeff(rgb_coeff, d->light.color,
			d->light.brightness * cosfactor(d->light.point, i));
		//i.color = adjust_brightness(i.color, 0.8);
	}
	//apply_light(d, &i, ray);
	i.color.trgb = apply_coeff(i.color, rgb_coeff);
	return (i.color.trgb);
}

int	apply_coeff(t_color color, t_rgb rgb_coeff)
{
	color.r *= rgb_coeff.r;
	color.g *= rgb_coeff.g;
	color.b *= rgb_coeff.b;
	if (color.r > 255)
		color.r = 255;
	if (color.g > 255)
		color.g = 255;
	if (color.b > 255)
		color.b = 255;
	color.trgb = 0x00FFFFFF & (color.r << 16 | color.g << 8 | color.b);
	return (color.trgb);
}

t_color	adjust_brightness(t_color color, double factor)
{
	color.r *= factor;
	color.g *= factor;
	color.b *= factor;
	if (color.r > 255)
		color.r = 255;
	if (color.g > 255)
		color.g = 255;
	if (color.b > 255)
		color.b = 255;
	color.trgb = 0x00FFFFFF & (color.r << 16 | color.g << 8 | color.b);
	return (color);
}

t_intrsct	get_objintersect(t_objlist *objlist, t_ray ray)
{
	t_intrsct	i;
	t_intrsct	i_new;

	i.color.trgb = 0xFF000000;
	i.distance = INFINITY;
	i.objnode = NULL;
	while (objlist)
	{
		i_new = objlist->get_intersection(ray, objlist->object);
		if (i_new.distance < i.distance)
		{
			i = i_new;
			i.objnode = objlist;
		}
		objlist = objlist->next;
	}
	return (i);
}

bool	is_shadowed(t_data *d, t_objlist *objlist, t_3d point)
{
	t_ray		shadow_ray;
	double		light_dist;
	double		block_dist;

	light_dist = distance(point, d->light.point);
	shadow_ray.direction = norm(subtract(d->light.point, point));
	shadow_ray.origin = point;
	while (objlist)
	{
		block_dist = objlist->get_intersection(shadow_ray, objlist->object).distance;
		if (block_dist - light_dist < EPSILON)
			return (true);
		objlist = objlist->next;
	}
	return (false);

}
