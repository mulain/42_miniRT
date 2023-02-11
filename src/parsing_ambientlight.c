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
	int		i;
	char	**subelements;

	if (d->amb_light.declared)
	{
		free_2d_char(elements);
		exit_free(d, E_AMBLIGHTDEF);
	}
	i = 0;
	if (!is_decimalformat(elements[1]))
	{
		free_2d_char(elements);
		exit_free(d, E_AMBLIGHT1);
	}
	subelements = ft_split(elements[2], ',');
	free_2d_char(elements);
	if (!is_uchartriplet(subelements))
	{
		free_2d_char(subelements);
		exit_free(d, E_AMBLIGHT2);
	}
	free_2d_char(subelements);
}
