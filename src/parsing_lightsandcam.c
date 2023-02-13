# include "../incl/minirt.h"

/*
Subject example:
Ambient lighting:
A 0.2 255,255,255
∗ identifier: A (-> elements[0])
∗ ambient lighting ratio in range [0.0,1.0]: 0.2 (-> elements[1])
∗ R,G,B colors in range [0-255]: 255, 255, 255 (-> elements[2])
*/
void	parse_ambientlight(t_data *d)
{
	if (d->amb_light.declared)
		exit_free(d, E_AMBLIGHTDEF);
	d->amb_light.declared = true;
	d->parse.min = 0.0;
	d->parse.max = 1.0;
	parse_double(d, &d->amb_light.brightness, 1, E_AMBLIGHT1);
	parse_tcolor(d, &d->amb_light.color, 2, E_AMBLIGHT2);
	free_2d_char(d->parse.elmnts);
	d->parse.elmnts = NULL;
	print_ambientlight(d);
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
void	parse_camera(t_data *d)
{
	if (d->camera.declared)
		exit_free(d, E_CAMERADEF);
	d->camera.declared = true;
	parse_tpoint(d, &d->camera.viewpoint, 1, E_CAMERA1);
	parse_tnormvector(d, &d->camera.normvector, 2, E_CAMERA2);
	d->parse.min = 0;
	d->parse.max = 180;
	parse_int(d, &d->camera.fieldofview, 3, E_CAMERA3);
	free_2d_char(d->parse.elmnts);
	d->parse.elmnts = NULL;
	print_camera(d);
}
