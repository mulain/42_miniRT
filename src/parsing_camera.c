# include "../incl/minirt.h"

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
	check_camera_declared(d, elements);
	set_camera_viewpoint(d, elements);
	set_camera_normvector(d, elements);
	set_camera_fieldofview(d, elements);
	free_2d_char(elements);
	print_camera(d);
}

void	check_camera_declared(t_data *d, char **elements)
{
	if (d->camera.declared)
	{
		free_2d_char(elements);
		exit_free(d, E_CAMERADEF);
	}
	d->camera.declared = true;
}

void	set_camera_viewpoint(t_data *d, char **elements)
{
	int		i;
	char	**subelements;

	if (!elements[1])
	{
		free_2d_char(elements);
		exit_free(d, E_CAMERA1);
	}
	subelements = ft_split(elements[1], ',');
	i = 0;
	while (subelements[i])
		i++;
	if (i < 2 || !set_tpoint(&d->camera.viewpoint, subelements))
	{
		free_2d_char(elements);
		free_2d_char(subelements);
		exit_free(d, E_CAMERA1);
	}
	free_2d_char(subelements);
}

/*
Haven't understood the concept of the normvector 100 % yet.
If the length is really always 1, then additional logical check is needed.
So far only check individual numbers for not exceeding -1 to 1.
*/
void	set_camera_normvector(t_data *d, char **elements)
{
	int		i;
	char	**subelements;

	if (!elements[2])
	{
		free_2d_char(elements);
		exit_free(d, E_CAMERA2);
	}
	subelements = ft_split(elements[2], ',');
	i = 0;
	while (subelements[i])
		i++;
	if (i < 2 || !set_tnormvector(&d->camera.normvector, subelements))
	{
		free_2d_char(elements);
		free_2d_char(subelements);
		exit_free(d, E_CAMERA2);
	}
	free_2d_char(subelements);
}

void	set_camera_fieldofview(t_data *d, char **elements)
{
	if (!elements[3])
	{
		free_2d_char(elements);
		exit_free(d, E_CAMERA3);
	}
	if (!set_int(&d->camera.fieldofview, elements[3], 0, 180))
	{
		free_2d_char(elements);
		exit_free(d, E_CAMERA3);
	}
}
