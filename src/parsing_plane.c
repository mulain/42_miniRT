# include "../incl/minirt.h"

/*
Plane:
pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
∗ identifier: pl (-> elements[0])
∗ x,y,z coordinates: 0.0,0.0,-10.0 (-> elements[1])
∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0 (-> elements[2])
∗ R,G,B colors in range [0-255]: 0, 0, 255 (-> elements[3])
*/


void	parse_plane(t_data *d, char **elements)
{
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		exit_free(d, E_MALLOC);
	set_plane_anchor(d, plane, elements);
	set_plane_vector(d, plane, elements);
	set_plane_color(d, plane, elements);
	objlst_add_back(&d->objectlist, objlst_new(plane, pl, &calc_plane));
	free_2d_char(elements);
}

void	set_plane_vector(t_data *d, t_plane *plane, char **elements)
{
	int		i;
	char	**subelements;

	if (!elements[2])
	{
		free_2d_char(elements);
		exit_free(d, E_PLANE1);
	}
	subelements = ft_split(elements[2], ',');
	i = 0;
	while (subelements[i])
		i++;
	// if (i < 2 || !set_tpoint(&plane->anchor, subelements))
	if (i < 2 || !set_tpoint(&plane->orientation_vector, subelements))

	{
		free_2d_char(elements);
		free_2d_char(subelements);
		exit_free(d, E_PLANE1);
	}
	free_2d_char(subelements);
}

void	set_plane_anchor(t_data *d, t_plane *plane, char **elements)
{
	int		i;
	char	**subelements;

	if (!elements[1])
	{
		free_2d_char(elements);
		exit_free(d, E_PLANE1);
	}
	subelements = ft_split(elements[1], ',');
	i = 0;
	while (subelements[i])
		i++;
	// if (i < 2 || !set_tpoint(&plane->anchor, subelements))
	if (i < 2 || !set_tpoint(&plane->anchr, subelements))

	{
		free_2d_char(elements);
		free_2d_char(subelements);
		exit_free(d, E_PLANE1);
	}
	free_2d_char(subelements);
}

void	set_plane_color(t_data *d, t_plane *plane, char **elements)
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
	if (i < 2 || !set_tcolor(&plane->color, subelements))
	{
		free_2d_char(elements);
		free_2d_char(subelements);
		exit_free(d, E_SPHERE3);
	}
	free_2d_char(subelements);
}