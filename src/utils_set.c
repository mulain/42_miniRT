# include "../incl/minirt.h"

bool	set_double(double *target, char *input, double min, double max)
{
	double	val;

	val = ft_strtod(input);
	if (!is_decimalformat(input) || val < min || val > max)
		return (false);
	*target = ft_strtod(input);
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
	*point = (t_point){ft_strtod(arr[0]), ft_strtod(arr[1]), ft_strtod(arr[2])};
	return (true);
}

bool	set_tnormvector(t_normvector *vec, char **arr)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!is_decimalformat(arr[i])
			|| ft_strtod(arr[i]) < -1 || ft_strtod(arr[i]) > 1.0)
			return (false);
		i++;
	}
	*vec = (t_normvector){ft_strtod(arr[0]), ft_strtod(arr[1]),
		ft_strtod(arr[2])};
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
