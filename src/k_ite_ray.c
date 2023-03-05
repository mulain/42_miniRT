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

t_color	parse_intersection(t_vector d, t_data *data)
{
	double	ret;
	double	min_dist;
	t_color	ret_color;
	t_objlist	*parsing;
	t_color	bgm;
	// int		i;

	// i = 0;

	bgm.r = 0;
	bgm.g = 0;
	bgm.b = 0;

	min_dist = INFINITY;
	//printf("in intersect\n");
	parsing = data->objectlist;
	while (parsing)
	{
		// printf("round %i\n", i);
		// i++;
		ret = parsing->formula(parsing->content, d, data);
		if (ret < min_dist && ret > 0.0001)
		{
			// printf("new min_dist %lf\n", ret);
			ret_color = (*data).tmp_color;
			min_dist = ret;
		}
		parsing = parsing->next;
	}
	if (min_dist == INFINITY)
	{
		ret_color = bgm;
	}
	return (ret_color);
}

void	ite_ray(t_data *data)
{
	int	i;
	int	j;
	t_vector	d;
	t_color	cl;

	j = 0;
	get_info_cam(&((*data).camera));
	printf("in iteray\n");
	while(j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			// printf("1\n");

			d = find_pixel_coord(i, j, data);
			// printf("2\n");

			cl = parse_intersection(d, data);
			// printf("3\n");
			// printf("r = %i\n", (*cl).r);
			my_put_pixel(data, i, j, cl);
			// printf("4\n");

			i++;
		}
		j++;
	}

}