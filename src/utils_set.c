# include "../incl/minirt.h"

/*
Define range constraints with min and max.
If no constraints should be respected: pass min == max.
*/
bool	set_double(double *target, char *input, double min, double max)
{
	double	val;

	if (!is_decimalformat(input))
		return (false);
	val = conv_strtod(input);
	if (min == max)
	{
		*target = conv_strtod(input);
		return (true);
	}
	if (val < min || val > max)
		return (false);
	*target = conv_strtod(input);
	return (true);
}

bool	set_tcolor(t_color *color, char **arr)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!is_ucharformat(arr[i]))
			return (false);
		i++;
	}
	*color = (t_color){ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2])};
	return (true);
}

bool	set_tpoint(t_point *point, char **arr)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!is_decimalformat(arr[i]))
			return (false);
		i++;
	}
	*point = (t_point){conv_strtod(arr[0]), conv_strtod(arr[1]), conv_strtod(arr[2])};
	return (true);
}

bool	set_tnormvector(t_normvector *vec, char **arr)
{
	int		i;
	double	x;
	double	y;
	double	z;

	i = 0;
	while (i < 3)
	{
		if (!is_decimalformat(arr[i]))
			return (false);
		i++;
	}
	x = conv_strtod(arr[0]);
	y = conv_strtod(arr[1]);
	z = conv_strtod(arr[2]);
	if (x < -1.0 || x > 1.0 || y < -1.0 || y > 1.0 || z < -1.0 || z > 1.0
		|| sqrt(x * x + y * y + z * z) != 1.0)
		return (false);
	*vec = (t_normvector){x, y, z};
	return (true);
}

bool	set_int(int *target, char *input, int min, int max)
{
	int		val;

	val = ft_atoi(input);
	if (!is_onlydigits(input) || val < min || val > max)
		return (false);
	*target = val;
	return (true);
}
