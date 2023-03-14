
#include "../incl/minirt.h"

/*
Not adding light directly, because it would require the if > 255 part to run
for each color update.
By only modifying the coefficient, this approach only has to run it once 
when the coefficient is applied and the final result is calculated.
*/
void	add_light(t_rgb *coeff, t_color lightcolor, double brightness)
{
	coeff->r += lightcolor.r / 255 * brightness;
	coeff->g += lightcolor.g / 255 * brightness;
	coeff->b += lightcolor.b / 255 * brightness;
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

int	add_colors(int color1, int color2, int color3)
{
	t_color		result;

	result.r = (0x00FF0000 & color1) >> 16;
	result.g = (0x0000FF00 & color1) >> 8;
	result.b = 0x000000FF & color1;
	result.r += (0x00FF0000 & color2) >> 16;
	result.g += (0x0000FF00 & color2) >> 8;
	result.b += 0x000000FF & color2;
	result.r += (0x00FF0000 & color3) >> 16;
	result.g += (0x0000FF00 & color3) >> 8;
	result.b += 0x000000FF & color3;
	if (result.r > 255)
		result.r = 255;
	if (result.g > 255)
		result.g = 255;
	if (result.b > 255)
		result.b = 255;
	result.trgb = 0x00FFFFFF & (result.r << 16 | result.g << 8 | result.b);
	return (result.trgb);
}

/*
Function does not perform input checking and can only be used
to illuminate one object with one light.
It is assumed that inputs are in valid bounds:
-	brightness not greater than 1.0
-	r, g, b values not greater than 255
*/
int	direct_light(t_color objcolor, t_color lightcolor, double brightness)
{
	objcolor.r *= lightcolor.r / 255 * brightness;
	objcolor.g *= lightcolor.g / 255 * brightness;
	objcolor.b *= lightcolor.b / 255 * brightness;
	objcolor.trgb
		= 0x00FFFFFF & (objcolor.r << 16 | objcolor.g << 8 | objcolor.b);
	return (objcolor.trgb);
}
