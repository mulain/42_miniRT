# include "../incl/minirt.h"

/*
Syntax example:
A 0.2 255,255,255
Line has already been strtrimmed for whitespace.
This function gets called if first char is 'A'.
i is initialized to 1 to skip 'A'.
Next non whitespace position is lighting with a range of 0.0 to 1.0 
*/
void parse_ambientlight(t_data *d, char *line)
{
	int		i;
	int		j;
	char	*amb_light;

	if (d->amb_light.declared)
	{
		free(line);
		exit_free(E_AMBLIGHT);
	}
	i = 1;
	while (line[i] && is_whitespace(line[i]))
		i++;
	if (!line[i])
	{
		free(line);
		exit_free(E_AMBLIGHT);
	}
	j = i;
	while (line[j] && !is_whitespace(line[j]))
		j++;
	amb_light = malloc((j - i + 1) * sizeof(char));
	ft_strlcpy(amb_light, line + i, j - i + 1);
	printf("amblight:'%s'\n", amb_light);
}
