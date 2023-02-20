# include "../incl/minirt.h"

static void	put_pixel(t_data *data, int x, int y, t_color color)
{
	int	i;

	i = (x * (*data).mlx.img_bytespp)
			+ (y * (*data).mlx.img_line_length);

	(*data).mlx.img_addr[i] = color.b;
	(*data).mlx.img_addr[++i] = color.g;
	(*data).mlx.img_addr[++i] = color.r;
	(*data).mlx.img_addr[++i] = 1;
}

int	calculate(t_plane pl, t_vector d, t_data data)
{
	double	t;
	double	div;
	t_vector norm;

	norm.x = pl.orientation_vector.x;
	norm.y = pl.orientation_vector.y;
	norm.z = pl.orientation_vector.z;

	div = dot(d, norm);
	if (div == 0)
	{
		return (0);
	}
	
	t = (dot(pl.anchr, norm) - dot(data.camera.org, norm)) / div;
	// printf("t = %lf\n", t);

	if (t > 0.0001 && t != INFINITY)
	{
		return (1);
	}
	else 
	{
		return (0);
	}
}

void	find_pixel_coord(double	x, double y, t_data *data)
{
	t_plane		*pl;
	t_vector	ret;
	t_vector	d;
	t_camdata	cm;

	
	cm = (*data).camera.camdata;
	pl = (t_plane*)(*data).objectlist[0].content;

	ret.x = (x + 0.5) * 2 / WIDTH - 1;
	ret.y = 1 - (y + 0.5) * 2 / HEIGHT;
	ret.z = 0;

	d = sum(scale_to(cm.right, ret.x), scale_to(cm.up, ret.y));
	d = sum(d, (*data).camera.normvector);

	// equalize(&d, norml(extr(d, (*data).camera.org)));
	// equalize(&d, norml(d));
	
	if (calculate(*pl, d, *data))
	{
		// printf("YAAAASSSS\n");
		put_pixel(data, x, y, (*pl).color);

	}

}