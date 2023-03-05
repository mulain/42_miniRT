
#include "../incl/minirt.h"

/*
Will not test range if min == max.
*/
double	parse_double(t_data *d, char *input, char *msg)
{
	double		value;

	if (!input || !is_decimalformat(input))
		error_exit(d, msg);
	value = conv_strtod(input);
	if (d->parse.min == d->parse.max)
		return (value);
	if (value < d->parse.min || value > d->parse.max)
		error_exit(d, msg);
	return (value);
}

t_color	parse_color(t_data *d, char *input, char *msg)
{
	int			i;
	char		**split;
	t_color		color;

	if (!input)
		error_exit(d, msg);
	d->parse.subelmnts = ft_split(input, ',');
	split = d->parse.subelmnts;
	if (count_subelements(split) != 3)
		error_exit(d, msg);
	i = -1;
	while (++i < 3)
		if (!is_ucharformat(split[i]))
			error_exit(d, msg);
	color.r = ft_atoi(split[0]);
	color.g = ft_atoi(split[1]);
	color.b = ft_atoi(split[2]);
	//color.trgb = 0x00FFFFFF & (color.r << 16 | color.g << 8 | color.b);
	color.trgb = 0x00000000;
	color.brightness = 0;
	free_2d_char(split);
	d->parse.subelmnts = NULL;
	return (color);
}

t_3d	parse_point(t_data *d, char *input, char *msg)
{
	int			i;
	char		**split;
	t_3d	point;

	if (!input)
		error_exit(d, msg);
	d->parse.subelmnts = ft_split(input, ',');
	split = d->parse.subelmnts;
	if (count_subelements(split) != 3)
		error_exit(d, msg);
	i = -1;
	while (++i < 3)
		if (!is_decimalformat(split[i]))
			error_exit(d, msg);
	point = (t_3d){conv_strtod(split[0]), conv_strtod(split[1]),
		conv_strtod(split[2])};
	free_2d_char(split);
	d->parse.subelmnts = NULL;
	return (point);
}

t_3d	parse_vector(t_data *d, char *input, char *msg)
{
	int			i;
	char		**split;
	t_3d	vector;

	if (!input)
		error_exit(d, msg);
	d->parse.subelmnts = ft_split(input, ',');
	split = d->parse.subelmnts;
	if (count_subelements(split) != 3)
		error_exit(d, msg);
	i = -1;
	while (++i < 3)
		if (!is_decimalformat(split[i]))
			error_exit(d, msg);
	vector = (t_3d){conv_strtod(split[0]), conv_strtod(split[1]),
		conv_strtod(split[2])};
	free_2d_char(split);
	d->parse.subelmnts = NULL;
	if (vector.x < -1.0 || vector.x > 1.0 || vector.y < -1.0 || vector.y > 1.0
		|| vector.z < -1.0 || vector.z > 1.0)
		error_exit(d, msg);
	if (vector.x == 0 && vector.y == 0 && vector.z == 0)
		error_exit(d, msg);
	return (norm(vector));
}

int	parse_int(t_data *d, char *input, char *msg)
{
	int		value;

	if (!input || !is_onlydigits(input))
		error_exit(d, msg);
	value = ft_atoi(input);
	if (d->parse.min == d->parse.max)
		return (value);
	if (value < (int)d->parse.min || value > (int)d->parse.max)
		error_exit(d, msg);
	return (value);
}
