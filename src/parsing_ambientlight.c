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
	check_declared_amblight(d, elements);
	set_amblight_lightingratio(d, elements);
	printf("double:%f\n", d->amb_light.brightness);
	set_amblight_color(d, elements);
	printf("color r:%i\ncolor g:%i\ncolor b:%i\n", d->amb_light.color.r, d->amb_light.color.g, d->amb_light.color.b);
}

void	check_declared_amblight(t_data *d, char **elements)
{
	if (d->amb_light.declared)
	{
		free_2d_char(elements);
		exit_free(d, E_AMBLIGHTDEF);
	}
	d->amb_light.declared = true;
}

void	set_amblight_lightingratio(t_data *d, char **elements)
{
	if (!elements[1] || !set_double(&d->amb_light.brightness, elements[1]))
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
	free_2d_char(elements);
	i = 0;
	while (subelements[i])
		i++;
	if (i < 2 || !set_tcolor(&d->amb_light.color, subelements))
	{
		free_2d_char(subelements);
		exit_free(d, E_AMBLIGHT2);
	}
	free_2d_char(subelements);
}



/*
Subject example:
Camera:
C -50.0,0,20 0,0,1 70
∗ identifier: C (-> elements[0])
∗ x,y,z coordinates of the view point: 0.0,0.0,20.6 (-> elements[1])

∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0 (-> elements[2])
∗ FOV : Horizontal field of view in degrees in range [0,180] (-> elements[3])
*/
void	parse_camera(t_data *d, char **elements)
{
	char	**subelements;

	if (d->camera.declared)
	{
		free_2d_char(elements);
		exit_free(d, E_CAMERADEF);
	}
	d->camera.declared = true;
	subelements = ft_split(elements[1], ',');
	if (!set_tpoint(&d->camera.viewpoint, subelements))
	{
		free_2d_char(elements);
		free_2d_char(subelements);
		exit_free(d, E_CAMERA1);
	}
	printf("viewpoint_x:%f\nviewpoint_y:%f\nviewpoint_z:%f\n", d->camera.viewpoint.x, d->camera.viewpoint.y, d->camera.viewpoint.z);
	free(subelements);
	subelements = ft_split(elements[2], ',');
	if (!set_tnormvector(&d->camera.normvector, subelements))
	{
		free_2d_char(elements);
		free_2d_char(subelements);
		exit_free(d, E_CAMERA1);
	}
	/* if (!set_double(&d->amb_light.brightness, elements[1]))
	{
		free_2d_char(elements);
		exit_free(d, E_AMBLIGHT1);
	}
	printf("double:%f\n", d->amb_light.brightness);
	subelements = ft_split(elements[2], ',');
	free_2d_char(elements);
	if (!set_tcolor(&d->amb_light.color, subelements))
	{
		free_2d_char(subelements);
		exit_free(d, E_AMBLIGHT2);
	}
	printf("color r:%i\ncolor g:%i\ncolor b:%i\n", d->amb_light.color.r, d->amb_light.color.g, d->amb_light.color.b); */
	free_2d_char(elements);
	free_2d_char(subelements);
}