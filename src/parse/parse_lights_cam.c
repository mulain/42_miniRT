
#include "minirt.h"

void	parse_ambientlight(t_data *d)
{
	if (d->amb_light.declared)
		error_exit(d, E_AMBLIGHTDEF);
	d->amb_light.declared = true;
	d->parse.min = 0.0;
	d->parse.max = 1.0;
	d->amb_light.brightness = parse_double(d, d->parse.elmnts[1], E_AMBLIGHT1);
	d->amb_light.color = parse_color(d, d->parse.elmnts[2], E_AMBLIGHT2);
}

void	parse_light(t_data *d)
{
	t_light		*light;

	light = malloc(sizeof(t_light));
	if (!light)
		error_exit(d, E_MALLOC);
	lightlst_add_back(&d->lightlst, lightlst_new(d, light));
	light->origin = parse_point(d, d->parse.elmnts[1], E_LIGHT1);
	d->parse.min = 0.0;
	d->parse.max = 1.0;
	light->brightness = parse_double(d, d->parse.elmnts[2], E_LIGHT2);
	light->color = parse_color(d, d->parse.elmnts[3], E_LIGHT3);
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
	d->fov_ratio = tan(to_rad(d->camera.fieldofview / 2));
	d->camera.x_axis = cross((t_3d){0, 1, 0}, reverse(d->camera.vector));
	d->camera.y_axis = cross(d->camera.x_axis, d->camera.vector);
}
