
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
	t_vector	point;

	point.x = (2 * (x + 0.5) / d->width - 1) * d->aspect_ratio * d->fov_ratio;
	point.y = (1 - 2 * (y + 0.5) / d->height) * d->fov_ratio;
	point.z = -1;
	return (point);
}

t_vector	get_vector(t_data *d, int x, int y)
{
	t_vector	looking;

	looking = point_subtract(d->camera.point, pixel_to_point(d, x, y));
	//upguide = t_vector{0, 1, 0};
	return (vector_normalize(looking));
	

	
	
	
}

/* transform ray
 Vector3 cameraRight = cross(cameraDirection, cameraUp);
        Vector3 worldDirection = {
            cameraRight.x * rayDirection.x + cameraUp.x * rayDirection.y + cameraDirection.x * rayDirection.z,
            cameraRight.y * rayDirection.x + cameraUp.y * rayDirection.y + cameraDirection.y * rayDirection.z,
            cameraRight.z * rayDirection.x + cameraUp.z * rayDirection.y + cameraDirection.z * rayDirection.z
        };
        worldDirection = normalize(worldDirection); */

int	trace(t_data *d, t_vector vec, int depth)
{
	(void)depth;
	t_objlist		*temp;
	t_ray			ray;

	ray.point = d->camera.point;
	ray.vector = vec;
	temp = d->objectlist;
	while (temp)
	{
		if (temp->objtype == sp)
		{
			if (intersect_sphere(ray, (t_sphere *)temp->content) != INFINITY);
				return (0x00FFFFFF);
			else
				return (0x00000000);
		}
		if (temp->objtype == pl)
		{
			if (intersect_plane(ray, (t_plane *)temp->content) != INFINITY);
				return (0x00FF00FF);
			else
				return (0x00000000);
		}
	}
	return (0);
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
