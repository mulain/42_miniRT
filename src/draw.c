
#include "../incl/minirt.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*pxl;

	pxl = mlx->img_addr + (y * mlx->img_line_length + x * mlx->img_bytespp);
	*(unsigned int *)pxl = color;
	
	/* *(unsigned int *) \
	(mlx->img_addr + y * mlx->img_line_length + x * mlx->img_bytespp) = color */;
}

/*
Coordinate system from -1 to 1
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
	t_vector	upguide;
	t_vector	x_axis;
	t_vector	y_axis;
	t_vector	transformed;

	looking = point_subtract(d->camera.point, pixel_to_point(d, x, y));
	upguide = (t_vector){0, 1, 0};
	x_axis = vector_normalize(vector_crossprod(upguide, d->camera.vector));
	y_axis = vector_normalize(vector_crossprod(x_axis, d->camera.vector));
	transformed = point_add(vector_multiply(x_axis, looking.x), d->camera.vector);
	transformed = point_add(vector_multiply(y_axis, looking.y), transformed);
	return (vector_normalize(transformed));
}

/* transform ray
 Vector3 cameraRight = cross(cameraDirection, cameraUp);
        Vector3 worldDirection = {
            cameraRight.x * rayDirection.x + cameraUp.x * rayDirection.y + cameraDirection.x * rayDirection.z,
            cameraRight.y * rayDirection.x + cameraUp.y * rayDirection.y + cameraDirection.y * rayDirection.z,
            cameraRight.z * rayDirection.x + cameraUp.z * rayDirection.y + cameraDirection.z * rayDirection.z
        };
        worldDirection = normalize(worldDirection); */

int	trace_ray(t_data *d, t_objlist *objs, t_ray ray)
{
	t_intrsct	intersection;
	t_intrsct	temp;

	(void)d;
	intersection.color = 0xFF000000;
	intersection.distance = INFINITY;
	while (objs)
	{
		if (objs->objtype == sp)
			temp = intersect_sphere(ray, *(t_sphere *)objs->content);
		else if (objs->objtype == pl)
			temp = intersect_plane(ray, *(t_plane *)objs->content);
		else if (objs->objtype == cy)
			temp = intersect_cylinder(ray, *(t_cylinder *)objs->content);
		if (temp.distance < intersection.distance)
			intersection = temp;
		objs = objs->next;
	}
	return (intersection.color);
}

void	render(t_data *d)
{
	int		x;
	int		y;
	t_ray	ray;

	ray.point = d->camera.point;
	y = 0;
	while (y < d->height)
	{
		x = 0;
		while (x < d->width)
		{
			ray.vector = get_vector(d, x, y);
			put_pixel(&d->mlx, x, y, trace_ray(d, d->objectlist, ray));
			x++;
		}
		printf("\rRendering: %.0f%%", (double)y / (d->height - 1) * 100);
		y++;
	}
	printf("\n");
	mlx_put_image_to_window(d->mlx.mlx, d->mlx.win, d->mlx.img, 0, 0);
}
