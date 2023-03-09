
#include "../incl/minirt.h"

void	apply_light(t_data *d, t_intrsct *i, t_ray ray)
{
	t_3d	normal;
	t_3d	light_normal;
	double	cos_factor;
	//check for surface type if applicable, doing diffuse now
	(void)ray;
	normal = i->objnode->get_normal(i->point, i->objnode->object);
	light_normal = norm(subtract(i->point, d->light.point));
	cos_factor = dot(normal, light_normal) * -1;
	i->color = apply_brightness(i->color, cos_factor);
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

t_color	mult_colors(t_color color1, t_color color2)
{
	t_color		result;

	result.r = (color1.r * color2.r) / 255;
	result.g = (color1.g * color2.g) / 255;
	result.b = (color1.b * color2.b) / 255;
	result.trgb = 0x00FFFFFF & (result.r << 16 | result.g << 8 | result.b);
	return (result);
}

t_color	add_color(t_color color1, t_color color2)
{
	t_color		result;

	result.r = (color1.r * color1.brightness + color2.r * color2.brightness) * 0.5;
	result.g = (color1.g * color1.brightness + color2.g * color2.brightness) * 0.5;
	result.b = (color1.b * color1.brightness + color2.b * color2.brightness) * 0.5;
	result.brightness = (color1.brightness + color2.brightness) * 0.5;
	result.trgb = 0x00FFFFFF & (result.r << 16 | result.g << 8 | result.b);
	return (result);
}

t_color	add_amblight(t_color base, t_ambientlight light)
{
	base.r -= (255 - light.color.r) * 0.5;
	base.g -= (255 - light.color.g) * 0.5;
	base.b -= (255 - light.color.b) * 0.5;
	if (base.r < 0)
		base.r = 0;
	if (base.g < 0)
		base.g = 0;
	if (base.b < 0)
		base.b = 0;
	base.trgb = 0x00FFFFFF & (base.r << 16 | base.g << 8 | base.b);
	return (adjust_brightness(base, light.brightness));
}

int	trace_ray_old(t_data *d, t_ray ray)
{
	t_intrsct	i;
	t_rgb		rgb_coeff;

	i = get_objintersect(d->objectlist, ray);
	if (!i.objnode) // no intersection, return bckgcolor
		return (0x00000000);
	rgb_coeff = add_lighttocoeff((t_rgb){0, 0, 0},
			d->amb_light.color, d->amb_light.brightness);
	if (!is_shadowed(d->light, d->objectlist, i.point))
		rgb_coeff = add_lighttocoeff(rgb_coeff, d->light.color,
				d->light.brightness * cosfactor(d->light.origin, i));
	i.color.trgb = apply_coeff(i.color, rgb_coeff);
	return (i.color.trgb);
}

/*
This function assumes (correctly, for now) that cone and tube
structs are interchangeable.
*/
t_intrsct	intersect_cone(t_ray ray, void *obj)
{
	t_cone		*cone;
	t_intrsct	i;
	t_3d		base_to_p;
	t_3d		axis_point;
 	double		local_r;
	double		local_h;
	double		point_r;

	cone = (t_cone *)obj;
	i = intersect_tube(ray, cone);
	if (i.distance == INFINITY)
		return (i);

	base_to_p = subtract(i.point, cone->base);
	local_h = dot(base_to_p, cone->axis);
	local_r = 1 - local_h / cone->height;
	
	
	axis_point = add(cone->base, scale(cone->axis, local_h));
	point_r = distance(axis_point, i.point);
	
	if (point_r - local_r > EPSILON)
		i.distance = INFINITY;
	return (i);
}