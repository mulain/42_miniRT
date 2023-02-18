// # include "vectormath.h"
# include "../incl/minirt.h"





static void	put_pixel(t_data *data, int x, int y, t_color color)
{
	int	i;
	// t_mlx	*tmp;

	i = (x * (*data).mlx.img_bytespp)
			+ (y * (*data).mlx.img_line_length);

	(*data).mlx.img_addr[i] = color.b;
	(*data).mlx.img_addr[++i] = color.g;
	(*data).mlx.img_addr[++i] = color.r;
	(*data).mlx.img_addr[++i] = 1;
}

int	calculate(t_plane pl, t_vector ray_p)
{
	double	t;
	t_vector plane_p;
	t_vector norm;
	// t_color	cl;

	plane_p.x = pl.anchr.x;
	plane_p.y = pl.anchr.y;
	plane_p.z = pl.anchr.z;

	norm.x = pl.orientation_vector.x;
	norm.y = pl.orientation_vector.y;
	norm.z = pl.orientation_vector.z;

	t = (dot(plane_p, norm) - dot(ray_p, norm)) / dot(ray_p, norm);
	// printf("t = %lf", t);

	if (t <= 0.0001 || t >= 1 || t == 0)
	{
		return (0);
	}
	else
	{
		return (1);
		// put_pixel(base, z.width, z.height, pl.color);
	}
}

void	find_pixel_coord(double	x, double y, double	z, t_data *data)
{
	t_vector	ray_p;
	// t_vector	direction;
	t_plane		*pl;
	pl = (t_plane*)(*data).objectlist[0].content;

	ray_p.x = MIN_X + x * (MAX_X - MIN_X / WIDTH);
	ray_p.y = MAX_Y - y * (MAX_Y - MIN_Y / HEIGHT);
	ray_p.z = MAX_Z - z * (MAX_Y - MIN_Y / HEIGHT);

	if (calculate(*pl, ray_p))
	// if (1)
	{
		// printf("YAAAASSSS\n");
		put_pixel(data, x, y, (*pl).color);

	}

}

void	ite_ray(t_data *data)
{
	int	i;
	int	j;
	int	n;
	// t_plane		*pl;
	// pl = (t_plane*)(*data).objectlist[0].content;

	j = 0;
	printf("in iteray\n");
	while(j < HEIGHT)
	{
		i = 0;
		// printf("y = %i\n", j);

		while (i < WIDTH)
		{
			n = 0;
			while (n < DEAPTH)
			{
				find_pixel_coord(i, j, n, data);

				n++;
			}
			i++;
		}
		j++;
	}

}