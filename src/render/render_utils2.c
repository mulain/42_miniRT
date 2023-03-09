
#include "../incl/minirt.h"

void	add_lighttocoeff(t_rgb *coeff, t_color color, double brightness)
{
	coeff->r += color.r / 255 * brightness;
	coeff->g += color.g / 255 * brightness;
	coeff->b += color.b / 255 * brightness;
}

/* void	add_light(t_color *color, t_light light, double cosfactor)
{
	*color.r += light.color.r * light.brightness * cosfactor;
	*color.g += light.color.g * light.brightness * cosfactor;
	*color.b += light.color.b* light.brightness * cosfactor;
} */

/*
light 1: 255, 255, 255
-> rgb_coeff 1, 1, 1

light 2: 255, 0, 0,
-> rgb_coeff 1, 0, 0,

add light 1 and light 2
final rgb_coeff 2, 1, 1
result of normalizelight 1, 0.5, 0.5

*/
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

t_color	apply_brightness(t_color color, double brightness)
{
	color.r *= brightness;
	color.g *= brightness;
	color.b *= brightness;
	if (color.r > 255)
		color.r = 255;
	if (color.g > 255)
		color.g = 255;
	if (color.b > 255)
		color.b = 255;
	color.trgb = 0x00FFFFFF & (color.r << 16 | color.g << 8 | color.b);
	return (color);
}
