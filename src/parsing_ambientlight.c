# include "../incl/minirt.h"

/*
Subject example:
Ambient lighting:
A 0.2 255,255,255
∗ identifier: A (-> elements[0])
∗ ambient lighting ratio in range [0.0,1.0]: 0.2 (-> elements[1])
∗ R,G,B colors in range [0-255]: 255, 255, 255 (-> elements[2])
*/
void	parse_ambientlight(t_data *d, char **elements)
{
	check_amblight_declared(d, elements);
	set_amblight_brightness(d, elements);
	set_amblight_color(d, elements);
	free_2d_char(elements);
	print_ambientlight(d);
}

void	check_amblight_declared(t_data *d, char **elements)
{
	if (d->amb_light.declared)
	{
		free_2d_char(elements);
		exit_free(d, E_AMBLIGHTDEF);
	}
	d->amb_light.declared = true;
}

void	set_amblight_brightness(t_data *d, char **elements)
{
	if (!elements[1] || !set_double(&d->amb_light.brightness, elements[1], 0.0, 1.0))
	{
		free_2d_char(elements);
		exit_free(d, E_AMBLIGHT1);
	}
}

void	set_amblight_color(t_data *d, char **elements)
{
	int		i;
	char	**subelements;

	if (!elements[2])
	{
		free_2d_char(elements);
		exit_free(d, E_AMBLIGHT2);
	}
	subelements = ft_split(elements[2], ',');
	i = 0;
	while (subelements[i])
		i++;
	if (i < 2 || !set_tcolor(&d->amb_light.color, subelements))
	{
		free_2d_char(elements);
		free_2d_char(subelements);
		exit_free(d, E_AMBLIGHT2);
	}
	free_2d_char(subelements);
}