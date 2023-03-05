
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

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*pxl;

	pxl = mlx->img_addr + (y * mlx->img_line_length + x * mlx->img_bytespp);
	*(unsigned int *)pxl = color;
}

/*
Current structure (prolly shite:
- get objintersect gives info:
	- base color of hit obj
		- if none hit: black (implement bckg?)
	- distance traveled from camera
	- point of intersection
	- MISSING: normal of hit object!
*/
int	trace_ray(t_data *d, t_ray ray)
{
	t_intrsct	i;

	i = get_objintersect(d->objectlist, ray);
	//i.color = add_diffuse_light(i, ray);
	if (!is_shadowed(d, d->objectlist, i.point))
	{
		apply_light(d, &i, ray);
		//i.color = adjust_brightness(i.color, 0.8);
	}
	apply_ambientlight(d, &i);
	//i.color = add_shadow(d, d->objectlist, i);
	i.color = add_amblight(i.color, d->amb_light);
	return (i.color.trgb);
}

void	apply_ambientlight(t_data *d, t_intrsct *i)
{
	i->color = add_color(i->color, d->amb_light.color);
}

void	apply_light(t_data *d, t_intrsct *i, t_ray ray)
{
	t_3d	normal;
	t_3d	light_normal;
	double	cos_factor;
	//check for surface type if applicable, doing diffuse now
	(void)ray;
	if (!i->objnode)
		return ;
	normal = i->objnode->get_normal(i->point, i->objnode->object);
	light_normal = norm(subtract(i->point, d->light.point));
	cos_factor = dot(normal, light_normal) * -1;
	i->color = adjust_brightness(i->color, cos_factor);
}

/* 
float3 hitpoint = camray.origin + camray.dir * t;
 float3 normal = normalize(hitpoint - sphere1.pos);
 float cosine_factor = dot(normal, camray.dir) * -1.0f;
 
 output[work_item_id] = sphere1.color * cosine_factor;

 */

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
		// add pointer to the object that was hit?
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

t_color	add_shadow(t_data *d, t_objlist *objlist, t_intrsct i)
{
	t_ray		shadow_ray;
	t_intrsct	new_i;
	double		light_dist;

	light_dist = distance(i.point, d->light.point);
	shadow_ray.direction = norm(subtract(d->light.point, i.point));
	shadow_ray.origin = i.point;
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
