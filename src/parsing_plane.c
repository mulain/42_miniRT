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
		error_exit(d, E_MALLOC);
	set_plane_anchor(d, plane, elements);
	
	
	objlst_add_back(&d->objectlist, objlst_new(plane, pl));
	free_2d_char(elements);
}

void	set_plane_anchor(t_data *d, t_plane *plane, char **elements)
{
	int		i;
	char	**subelements;

	if (!elements[1])
	{
		free_2d_char(elements);
		error_exit(d, E_PLANE1);
	}
	subelements = ft_split(elements[1], ',');
	i = 0;
	while (subelements[i])
		i++;
	if (i < 2 || !set_tpoint(&plane->anchor, subelements))
	{
		free_2d_char(elements);
		free_2d_char(subelements);
		error_exit(d, E_PLANE1);
	}
	free_2d_char(subelements);
}