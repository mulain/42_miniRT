/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights_cam.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:46:24 by wmardin           #+#    #+#             */
/*   Updated: 2023/03/25 17:46:26 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambientlight(t_data *d)
{
	if (d->amb_light.declared)
		error_exit(d, E_AMBLIGHTDEF);
	d->amb_light.declared = true;
	set_range(d, 0.0, 1.0);
	d->amb_light.brightness = parse_double(d, d->parse.elmnts[1], E_AMBLIGHT1);
	d->amb_light.color = parse_color(d, d->parse.elmnts[2], E_AMBLIGHT2);
}

void	parse_light(t_data *d)
{
	t_light		light;

	light.origin = parse_point(d, d->parse.elmnts[1], E_LIGHT1);
	set_range(d, 0.0, 1.0);
	light.brightness = parse_double(d, d->parse.elmnts[2], E_LIGHT2);
	light.color = parse_color(d, d->parse.elmnts[3], E_LIGHT3);
	lightlst_add_back(&d->lightlst, lightlst_new(d, light));
}

void	parse_camera(t_data *d)
{
	if (d->camera.declared)
		error_exit(d, E_CAMERADEF);
	d->camera.declared = true;
	d->camera.point = parse_point(d, d->parse.elmnts[1], E_CAMERA1);
	d->camera.vector = parse_vector(d, d->parse.elmnts[2], E_CAMERA2);
	set_range(d, 0.0, 180.0);
	d->camera.fieldofview = parse_int(d, d->parse.elmnts[3], E_CAMERA3);
	d->fov_ratio = tan(to_rad(d->camera.fieldofview / 2));
	d->camera.x_axis = cross((t_3d){0, 1, 0}, reverse(d->camera.vector));
	d->camera.y_axis = cross(d->camera.x_axis, d->camera.vector);
}
