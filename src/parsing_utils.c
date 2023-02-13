# include "../incl/minirt.h"

void	parse_double(t_data *d, double *target, int index, char *msg)
{
	char	*input;

	input = d->parse.elmnts[index];
	if (!input || !is_decimalformat(input))
		exit_free(d, msg);
	*target = ft_strtod(input);
	if (d->parse.min == d->parse.max)
		return ;
	if (*target < d->parse.min || *target > d->parse.max)
		exit_free(d, msg);
}

void	parse_tcolor(t_data *d, t_color *color, int index, char *msg)
{
	int		i;
	char	**split;

	if (!d->parse.elmnts[index])
		exit_free(d, msg);
	d->parse.subelmnts = ft_split(d->parse.elmnts[index], ',');
	split = d->parse.subelmnts;
	if (count_subelements(split) < 3)
		exit_free(d, msg);
	i = 0;
	while (i < 3)
	{
		if (!is_ucharformat(split[i]))
			exit_free(d, msg);
		i++;
	}
	*color = (t_color){ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2])};
	free_2d_char(split);
	d->parse.subelmnts = NULL;
}

void	parse_tpoint(t_data *d, t_point *point, int index, char *msg)
{
	int		i;
	char	**split;

	if (!d->parse.elmnts[index])
		exit_free(d, msg);
	d->parse.subelmnts = ft_split(d->parse.elmnts[index], ',');
	split = d->parse.subelmnts;
	if (count_subelements(split) < 3)
		exit_free(d, msg);
	i = 0;
	while (i < 3)
	{
		if (!is_decimalformat(split[i]))
			exit_free(d, msg);
		i++;
	}
	*point = (t_point){ft_strtod(split[0]), ft_strtod(split[1]),
		ft_strtod(split[2])};
	free_2d_char(split);
	d->parse.subelmnts = NULL;
}

void	parse_tnormvector(t_data *d, t_normvector *vec, int index, char *msg)
{
	int		i;
	char	**split;

	if (!d->parse.elmnts[index])
		exit_free(d, msg);
	d->parse.subelmnts = ft_split(d->parse.elmnts[index], ',');
	split = d->parse.subelmnts;
	if (count_subelements(split) < 3)
		exit_free(d, msg);
	i = 0;
	while (i < 3)
	{
		if (!is_decimalformat(split[i]))
			exit_free(d, msg);
		i++;
	}
	*vec = (t_normvector){ft_strtod(split[0]), ft_strtod(split[1]),
		ft_strtod(split[2])};
	free_2d_char(split);
	d->parse.subelmnts = NULL;
	if (vec->x < -1.0 || vec->x > 1.0 || vec->y < -1.0 || vec->y > 1.0
		|| vec->z < -1.0 || vec->z > 1.0
		|| normvector_length(*vec) != 1.0)
		exit_free(d, msg);
}

void	parse_int(t_data *d, int *target, int index, char *msg)
{
	char	*input;

	input = d->parse.elmnts[index];
	if (!input || !is_onlydigits(input))
		exit_free(d, msg);
	*target = ft_atoi(input);
	if (d->parse.min == d->parse.max)
		return ;
	if (*target < (int)d->parse.min || *target > (int)d->parse.max)
		exit_free(d, msg);
}
