# include "../incl/minirt.h"

/*
Starts splitting at line + 1, because line[0] is the identifier.
*/
void	parse_ambientlight(t_data *d)
{
	int		i;
	int		val;

	if (d->amb_light.declared)
		exit_free(E_AMBLIGHT);
	d->elements_a = ft_split(d->line + 1, ' ');
	i = 0;
	while (d->elements_a[i])
	{
		printf("string %i:'%s'\n", i, d->elements_a[i]);
		i++;
	}
	if (!is_decimalformat(d->elements_a[0]))
		exit_free(E_AMBLIGHTDATA);
	d->elements_b = ft_split(d->elements_a[1], ',');
	
	//free_structvars(d);
}

/*
Syntax example:
A 0.2 255,255,255
Line has already been strtrimmed for whitespace.
This function gets called if first char is 'A'.
i is initialized to 1 to skip 'A'.
Next non whitespace position is lighting with a range of 0.0 to 1.0 
*/
void	parse_ambientlight_old(t_data *d, char *line)
{
	int		i;
	int		j;
	char	*temp;

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
		exit_free(E_AMBLIGHTDATA);
	}
	j = i;
	while (line[j] && !is_whitespace(line[j]))
		j++;
	temp = ft_substr(line, i, j - i); //use ft_substr as arg for atol
	/* temp = malloc((j - i + 1) * sizeof(char));
	ft_strlcpy(temp, line + i, j - i + 1); */
	printf("amblight_1:'%s'\n", temp);
	free (temp);
	temp = ft_substr(line, j, ft_strlen(line));
	printf("amblight_2:'%s'\n", temp);
	free (temp);
	free (line);
}
