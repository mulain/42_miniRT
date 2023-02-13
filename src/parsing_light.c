# include "../incl/minirt.h"

/*
Light:
L -40.0,50.0,0.0 0.6 10,0,255
∗ identifier: L (-> elements[0])
∗ x,y,z coordinates of the light point: 0.0,0.0,20.6 (-> elements[1])
∗ the light brightness ratio in range [0.0,1.0]: 0.6 (-> elements[2])
∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255 (-> elements[3])
*/
void	parse_light(t_data *d, char **elements)
{
	check_light_declared(d, elements);
	set_light_coordinates(d, elements);
	set_light_brightness(d, elements);
	set_light_color(d, elements);
	free_2d_char(&elements);
	print_light(d);
}

void	check_light_declared(t_data *d, char **elements)
{
	if (d->light.declared)
	{
		free_2d_char(&elements);
		exit_free(d, E_LIGHTDEF);
	}
	d->light.declared = true;
}

void	set_light_coordinates(t_data *d, char **elements)
{
	int		i;
	char	**subelements;

	if (!elements[1])
	{
		free_2d_char(&elements);
		exit_free(d, E_LIGHT1);
	}
	subelements = ft_split(elements[1], ',');
	i = 0;
	while (subelements[i])
		i++;
	if (i < 2 || !set_tpoint(&d->light.coordinates, subelements))
	{
		free_2d_char(&elements);
		free_2d_char(&subelements);
		exit_free(d, E_LIGHT1);
	}
	free_2d_char(&subelements);
}

void	set_light_brightness(t_data *d, char **elements)
{
	if (!elements[2] || !set_double(&d->light.brightness, elements[2], 0.0, 1.0))
	{
		free_2d_char(&elements);
		exit_free(d, E_LIGHT2);
	}
}

void	set_light_color(t_data *d, char **elements)
{
	int		i;
	char	**subelements;

	if (!elements[3])
	{
		free_2d_char(&elements);
		exit_free(d, E_LIGHT3);
	}
	subelements = ft_split(elements[3], ',');
	i = 0;
	while (subelements[i])
		i++;
	if (i < 2 || !set_tcolor(&d->light.color, subelements))
	{
		free_2d_char(&elements);
		free_2d_char(&subelements);
		exit_free(d, E_LIGHT3);
	}
	free_2d_char(&subelements);
}
