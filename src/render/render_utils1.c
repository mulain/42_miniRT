
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

	obj_normal = i.objnode->get_normal(i.point,
			light_origin, i.objnode->object);
	to_light_normal = norm(subtract(i.point, light_origin));
	return (dot(obj_normal, to_light_normal) * -1);
}

double	bright_diffuse(t_light light, t_intrsct i)
{
	double	cos_fac;

	cos_fac = cosfactor(light.origin, i);
	if (cos_fac < EPSILON)
		cos_fac = 0;
	return (cos_fac);
}