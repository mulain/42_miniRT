
#include "minirt.h"

void	set_pixel(t_mlx *mlx, int x, int y, int color)
{
	/*
	char	*pxl;

	pxl = d->img_addr + y * d->img_line_length + x * d->img_bytespp;
	*(unsigned int *)pxl = color;
	*/
	*(unsigned int *) \
	(mlx->img_addr + y * mlx->img_line_length + x * mlx->img_bytespp) = color;
}

/*
Coordinate system from -1 to 1 with camera at 0,0,0
Max range is from -1 to 1 = 2.
Points should therefore map to a range of 2 with values from -1 to 1.
To map the pixels to range of 2: take the normal percentage (value / maxvalue)
and multiply by 2.
To adjust that range (0 to 2) to range (-1 to 1) -> subtract 1. 
*/
t_point	pixel_to_point(t_data *d, int x, int y)
{
	t_point		point;

	point.x = 2 * x / d->width - 1;
	point.y = 2 * y / d->height - 1;

	forward vector = target - origin (normalized)
	right vector = forward x upguide (might mirror if wrong way around)
	up vector = right x forward

}
