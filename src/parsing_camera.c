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
	check_declared_camera(d, elements);
	set_camera_viewpoint(d, elements);
	printf("viewpoint_x:%f\nviewpoint_y:%f\nviewpoint_z:%f\n", d->camera.viewpoint.x, d->camera.viewpoint.y, d->camera.viewpoint.z);
	set_camera_normvector(d, elements);
	printf("cam_normvec.x:%f\ncam_normvec.y:%f\ncam_normvec.z:%f\n", d->camera.normvector.x, d->camera.normvector.y, d->camera.normvector.z);
	free_2d_char(elements);
}

void	check_declared_camera(t_data *d, char **elements)
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
	free(subelements);
}

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
	free(subelements);
}
