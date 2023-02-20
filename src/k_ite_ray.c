# include "../incl/minirt.h"

void	get_info_cam(t_camera *cam)
{
	t_vector	up_guide;
	t_camdata	cm;

	up_guide.x = 0;
	up_guide.y = 1;
	up_guide.z = 0;

	equalize(&(cm.right), norml(cross(cam->normvector, up_guide)));
	equalize(&(cm.up), cross(cm.right, cam->normvector));

	cam->camdata = cm;
}

void	ite_ray(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	get_info_cam(&((*data).camera));
	printf("in iteray\n");
	while(j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			find_pixel_coord(i, j, data);
			i++;
		}
		j++;
	}

}