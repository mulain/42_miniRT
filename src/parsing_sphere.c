# include "../incl/minirt.h"

/*
Sphere:
sp 0.0,0.0,20.6 12.6 10,0,255
∗ identifier: sp (-> elements[0])
∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6 (-> elements[1])
∗ the sphere diameter: 12.6 (-> elements[2])
∗ R,G,B colors in range [0-255]: 10, 0, 255 (-> elements[3])
*/
void	parse_sphere(t_data *d, char **elements)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		exit_free(d, E_MALLOC);
	set_sphere_center(d, sphere, elements);
	set_sphere_diameter(d, sphere, elements);
	set_sphere_color(d, sphere, elements);
	free_2d_char(elements);
}

void	set_sphere_center(t_data *d, t_sphere *sphere, char **elements)
{
	int		i;
	char	**subelements;

	if (!elements[1])
	{
		free_2d_char(elements);
		exit_free(d, E_SPHERE1);
	}
	subelements = ft_split(elements[1], ',');
	i = 0;
	while (subelements[i])
		i++;
	if (i < 2 || !set_tpoint(&sphere->center, subelements))
	{
		free_2d_char(elements);
		free_2d_char(subelements);
		exit_free(d, E_SPHERE1);
	}
	free_2d_char(subelements);
}

void	set_sphere_diameter(t_data *d, t_sphere *sphere, char **elements)
{
	if (!elements[2] || !set_double(&sphere->diameter, elements[2], 0.0, 1.0))
	{
		free_2d_char(elements);
		exit_free(d, E_SPHERE2);
	}
}

void	set_sphere_color(t_data *d, t_sphere *sphere, char **elements)
{
	int		i;
	char	**subelements;

	if (!elements[3])
	{
		free_2d_char(elements);
		exit_free(d, E_SPHERE3);
	}
	subelements = ft_split(elements[3], ',');
	i = 0;
	while (subelements[i])
		i++;
	if (i < 2 || !set_tcolor(&sphere->color, subelements))
	{
		free_2d_char(elements);
		free_2d_char(subelements);
		exit_free(d, E_SPHERE3);
	}
	free_2d_char(subelements);
}
