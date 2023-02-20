
#include "minirt.h"

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
		error_exit(d, E_AMBLIGHTDEF);
	d->amb_light.declared = true;
	d->parse.min = 0.0;
	d->parse.max = 1.0;
	d->amb_light.brightness = parse_double(d, d->parse.elmnts[1], E_AMBLIGHT1);
	d->amb_light.color = parse_tcolor(d, d->parse.elmnts[2], E_AMBLIGHT2);
}

/*
Light:
L -40.0,50.0,0.0 0.6 10,0,255
∗ identifier: L (-> elements[0])
∗ x,y,z point of the light point: 0.0,0.0,20.6 (-> elements[1])
∗ the light brightness ratio in range [0.0,1.0]: 0.6 (-> elements[2])
∗ (unused in mandatory)R,G,B colors in range [0-255]: 10, 0, 255 (-> elements[3])
*/
void	parse_light(t_data *d)
{
	if (d->light.declared)
		error_exit(d, E_LIGHTDEF);
	d->light.declared = true;
	d->light.point = parse_tpoint(d, d->parse.elmnts[1], E_LIGHT1);
	d->parse.min = 0.0;
	d->parse.max = 1.0;
	d->light.brightness = parse_double(d, d->parse.elmnts[2], E_LIGHT2);
	d->light.color = parse_tcolor(d, d->parse.elmnts[3], E_LIGHT3);
}

/*
Subject example:
Camera:
C -50.0,0,20 0,0,1 70
∗ identifier: C (-> elements[0])
∗ x,y,z point of the view point: 0.0,0.0,20.6 (-> elements[1])
∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0 (-> elements[2])
∗ FOV : Horizontal field of view in degrees in range [0,180] (-> elements[3])
*/
void	parse_camera(t_data *d)
{
	if (d->camera.declared)
		error_exit(d, E_CAMERADEF);
	d->camera.declared = true;
	d->camera.point = parse_tpoint(d, d->parse.elmnts[1], E_CAMERA1);
	d->camera.vector = parse_tvector(d, d->parse.elmnts[2], E_CAMERA2);
	d->parse.min = 0;
	d->parse.max = 180;
	d->camera.fieldofview = parse_int(d, d->parse.elmnts[3], E_CAMERA3);
}
