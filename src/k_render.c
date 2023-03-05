# include "../incl/minirt.h"

void	my_put_pixel(t_data *data, int x, int y, t_color color)
{
	int	i;

	i = (x * (*data).mlx.img_bytespp)
			+ (y * (*data).mlx.img_line_length);
	//printf("jnrlkmrlk\n");
	(*data).mlx.img_addr[i] = color.b;
	(*data).mlx.img_addr[++i] = color.g;
	(*data).mlx.img_addr[++i] = color.r;
	(*data).mlx.img_addr[++i] = 1;
}

double	calc_plane(void *plane, t_vector d, t_data *data)
{
	double	t;
	double	div;
	t_vector norm;
	t_plane	pl;
	pl = (*(t_plane *)plane);
	t_color	bgm;

	bgm.r = 0;
	bgm.g = 0;
	bgm.b = 0;

	norm.x = pl.orientation_vector.x;
	norm.y = pl.orientation_vector.y;
	norm.z = pl.orientation_vector.z;

	div = dot(d, norm);
	if (div == 0)
	{
		return (0);
	}
	
	t = (dot(pl.anchr, norm) - dot((*data).camera.org, norm)) / div;

	// printf("t = %lf\n", t);

	if (t > 0.0001 && t != INFINITY)
	{
		// data->tmp_color = (&pl.color);
		// tmp = pl.color;
		data->tmp_color = pl.color;
		//printf("r = %i", (*data).tmp_color->r);

	}
	else
	{
		// printf("kyky\n");
		(*data).tmp_color = bgm;
		// printf("r = %i", (*data).tmp_color.g);
		return (t);

	}
	return (t);
}

t_vector	find_pixel_coord(double	x, double y, t_data *data)
{
	// t_plane		*pl;
	t_vector	ret;
	t_vector	d;
	t_camdata	cm;

	
	cm = (*data).camera.camdata;
	ret.x = (x + 0.5) * 2 / WIDTH - 1;
	ret.y = 1 - (y + 0.5) * 2 / HEIGHT;
	ret.z = 0;

	d = sum(scale_to(cm.right, ret.x), scale_to(cm.up, ret.y));
	d = sum(d, (*data).camera.normvector);

	// equalize(&d, norml(extr(d, (*data).camera.org)));
	// equalize(&d, norml(d));

	return (d);

}

typedef struct s_helper
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		intersect_1;
	double		intersect_2;
}	t_helper;

double	calc_sphere(void *sphere, t_vector d, t_data *data)
{
	// t_vector	t;
	t_helper	h;
	t_sphere	sp;
	t_color	bgm;

	bgm.r = 0;
	bgm.g = 0;
	bgm.b = 0;

	// printf("in sphere\n");
	sp = (*(t_sphere *)sphere);

	// t = point_subtract((*data).camera.org, sp.center);
	h.a = vector_dotprod(d, d);
	h.b = 2 * vector_dotprod((*data).camera.org, d);
	h.c = vector_dotprod((*data).camera.org, (*data).camera.org) - sp.diameter * sp.diameter;
	h.discriminant = h.b * h.b - 4 * h.a * h.c;
	if (h.discriminant < 0)
	{
		(*data).tmp_color = bgm;

		return (INFINITY);

	}
	if (h.discriminant == 0)
	{
		// printf("zero\n");
		data->tmp_color = sp.color;
		return (-h.b / (2 * h.a));
	}
	h.intersect_1 = (-h.b - sqrt(h.discriminant)) / (2 * h.a);
	h.intersect_2 = (-h.b + sqrt(h.discriminant)) / (2 * h.a);
	if (h.intersect_2 < 0)
	{
		// printf("2 < 0\n");
		(*data).tmp_color = bgm;
		return (INFINITY);

	}
	if (h.intersect_1 >= 0)
	{
		printf("1 >= 0\n");

		data->tmp_color = sp.color;
		return (h.intersect_1);

	}
	else
	{
		// printf("else\n");
		data->tmp_color = sp.color;
		// (*data).tmp_color = bgm;
		return (h.intersect_2);
	}
}