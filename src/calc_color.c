
#include "../incl/minirt.h"

t_color	new_tcolor(int trgb)
{
	t_color		color;

	color.trgb = trgb;
	color.r = (0x00FF0000 & trgb) >> 16;
	color.g = (0x0000FF00 & trgb) >> 8;
	color.b = (0x000000FF & trgb);
	return (color);
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

t_color	add_light(t_color base, t_color light)
{
	base.r -= 255 - light.r;
	base.g -= 255 - light.g;
	base.b -= 255 - light.b;
	if (base.r < 0)
		base.r = 0;
	if (base.g < 0)
		base.g = 0;
	if (base.b < 0)
		base.b = 0;
	base.trgb = 0x00FFFFFF & (base.r << 16 | base.g << 8 | base.b);
	return (base);
}



/* t_color	adjust_brightness_oldmessedup(t_color color, double factor)
{

	color.r = ((0x00FF0000 & trgb) >> 16) * factor;
	if (color.r > 255)
		color.r = 255;
	color.g = ((0x0000FF00 & trgb) >> 8) * factor;
	if (color.g > 255)
		color.g = 255;
	color.b = (0x000000FF & trgb) * factor;
	if (color.b > 255)
		color.b = 255;
	color.trgb = 0x00FFFFFF & (color.r << 16 | color.g << 8 | color.b);
	return (color);
} */