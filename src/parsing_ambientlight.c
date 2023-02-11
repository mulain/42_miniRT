# include "../incl/minirt.h"

/*
Syntax example:
A 0.2 255,255,255
Line has already been strtrimmed for whitespace.
This function gets called if first char is 'A'.
i is initialized to 1 to skip 'A'.
Next non whitespace position is lighting with a range of 0.0 to 1.0

while (elements[i])
	{
		printf("string %i:'%s'\n", i, elements[i]);
		i++;
	}
*/
void	parse_ambientlight(t_data *d, char **elements)
{
	char	**subelements;

	if (d->amb_light.declared)
	{
		free_2d_char(elements);
		exit_free(d, E_AMBLIGHTDEF);
	}
	d->amb_light.declared = true;
	if (!set_double(&d->amb_light.brightness, elements[1]))
	{
		free_2d_char(elements);
		exit_free(d, E_AMBLIGHT1);
	}
	printf("double:%f\n", d->amb_light.brightness);
	subelements = ft_split(elements[2], ',');
	free_2d_char(elements);
	if (!set_uchartriplet(&d->amb_light.color, subelements))
	{
		free_2d_char(subelements);
		exit_free(d, E_AMBLIGHT2);
	}
	printf("color r:%i\ncolor g:%i\ncolor b:%i\n", d->amb_light.color.r, d->amb_light.color.g, d->amb_light.color.b);
	free_2d_char(subelements);
	printf("ok\n");
}
