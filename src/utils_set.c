# include "../incl/minirt.h"

bool	set_double(double *target, char *input)
{
	if (!is_decimalformat(input))
		return (false);
	*target = ft_strtod(input);
	return (true);
}

bool	set_uchartriplet(t_color *color, char **input)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!is_ucharformat(input[i]))
			return (false);
		i++;
	}
	*color = (t_color){ft_atoi(input[0]), ft_atoi(input[1]), ft_atoi(input[2])};
	return (true);
}
