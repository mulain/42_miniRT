# include "../incl/minirt.h"

void	parse_double(t_data *d, double *target, int index, char *msg)
{
	double	val;
	char	*input;

	input = d->parse.elmnts[index];
	if (!input || !is_decimalformat(input))
		exit_free(d, msg);
	val = ft_strtod(input);
	if (d->parse.min == d->parse.max)
	{
		*target = ft_strtod(input);
		return ;
	}
	if (val < d->parse.min || val > d->parse.max)
		exit_free(d, msg);
	*target = ft_strtod(input);
}

/*
Both char pointers are only to make it more readable.
Could get rid of both if u prefer.
*/
void	parse_tcolor(t_data *d, t_color *color, int index, char *msg)
{
	int		i;
	char	*input;
	char	**split;

	input = d->parse.elmnts[index];
	if (!input)
		exit_free(d, msg);
	d->parse.subelmnts = ft_split(input, ',');
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
}