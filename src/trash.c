
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