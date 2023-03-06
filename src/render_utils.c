
#include "../incl/minirt.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*pxl;

	pxl = mlx->img_addr + (y * mlx->img_line_length + x * mlx->img_bytespp);
	*(unsigned int *)pxl = color;
}

double	cosfactor(t_3d light_origin, t_intrsct i)
{
	t_3d	obj_normal;
	t_3d	to_light_normal;

	obj_normal =i.objnode->get_normal(i.point,i.objnode->object);
	to_light_normal = norm(subtract(i.point, light_origin));
	return (dot(obj_normal, to_light_normal) * -1);
}

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
	i->color = adjust_brightness(i->color, cos_factor);
}

t_rgb	add_lightcoeff(t_rgb main_rgb, t_color color, double brightness)
{
	main_rgb.r += color.r / 255 * brightness;
	main_rgb.g += color.g / 255 * brightness;
	main_rgb.b += color.b / 255 * brightness;
	return (main_rgb);
}
