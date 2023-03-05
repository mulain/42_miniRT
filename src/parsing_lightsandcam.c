
#include "minirt.h"

void	parse_ambientlight(t_data *d)
{
	if (d->amb_light.declared)
		error_exit(d, E_AMBLIGHTDEF);
	d->amb_light.declared = true;
	d->parse.min = 0.0;
	d->parse.max = 1.0;
	d->amb_light.brightness = parse_double(d, d->parse.elmnts[1], E_AMBLIGHT1);
	d->amb_light.color.brightness = parse_double(d, d->parse.elmnts[1], E_AMBLIGHT1);
	d->amb_light.color = parse_color(d, d->parse.elmnts[2], E_AMBLIGHT2);
}

void	parse_light(t_data *d)
{
	if (d->light.declared)
		error_exit(d, E_LIGHTDEF);
	d->light.declared = true;
	d->light.point = parse_point(d, d->parse.elmnts[1], E_LIGHT1);
	d->parse.min = 0.0;
	d->parse.max = 1.0;
	d->light.brightness = parse_double(d, d->parse.elmnts[2], E_LIGHT2);
	d->light.color.brightness = parse_double(d, d->parse.elmnts[2], E_LIGHT2);
	d->light.color = parse_color(d, d->parse.elmnts[3], E_LIGHT3);
}

/*
angle in radians = (angle in degrees) x (π/180)
*/
void	parse_camera(t_data *d)
{
	if (d->camera.declared)
		error_exit(d, E_CAMERADEF);
	d->camera.declared = true;
	d->camera.point = parse_point(d, d->parse.elmnts[1], E_CAMERA1);
	d->camera.vector = parse_vector(d, d->parse.elmnts[2], E_CAMERA2);
	d->parse.min = 0;
	d->parse.max = (double)180;
	d->camera.fieldofview = parse_int(d, d->parse.elmnts[3], E_CAMERA3);
	d->fov_ratio = tan((d->camera.fieldofview / 2) * M_PI / 180);
}
