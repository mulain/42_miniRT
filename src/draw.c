
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
To adjust that range from (0 to 2) to a range from (-1 to 1) -> subtract 1 for x
since x goes from left to right.
y however goes from top down, so we have to subtract the calculation from 1 to
have positive values for y above the x axis and negative ones below it.
Add 0.5 to each pixel to make the ray go through the middle of the pixel and
not its left (x) or top (y) border.
Multiply x by the aspect ratio to account for non square screens. This means that
the range of the x coordinates will shrink from or expand beyond -1 to 1 depending
on the ratio of image width and image height.
*/
t_vector	pixel_to_point(t_data *d, int x, int y)
{
	t_vector		point;

	point.x = 2 * (x + 0.5) / d->width - 1;
	point.x *= d->aspect_ratio;
	point.x *= d->fov_ratio;
	point.y = 1 - 2 * (y + 0.5) / d->height;
	point.y *= d->fov_ratio;
	point.z = -1;


/* 	forward vector = target - origin (normalized)
	right vector = forward x upguide (might mirror if wrong way around)
	up vector = right x forward */

}

void	render(t_data *d)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < d->height)
	{
		x = 0;
		while (x < d->width)
		{
			color = trace(d, get_vector(d, x, y), RAYDEPTH);
			set_pixel(d->mlx, x, y, color);
			printf("\rProgress: %i%%", y / d->height * 100);
			x++;
		}
		y++;
	}
}
