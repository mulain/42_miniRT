/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:46:05 by wmardin           #+#    #+#             */
/*   Updated: 2023/05/02 11:55:56 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minirt.h"

int	ambient_component(t_data *d, t_intrsct i)
{
	double	brightness;

	if (!i.objnode->phong.amb)
		return (0);
	brightness = d->amb_light.brightness * i.objnode->phong.amb;
	return (direct_light(i.color, d->amb_light.color, brightness));
}

int	diffuse_component(t_data *d, t_intrsct i, t_lightlst *light)
{
	double	cos_fac;

	if (!i.objnode->phong.diff)
		return (0);
	while (light)
	{
		if (!is_shadowed(light->origin, d->objectlist, i.point))
		{
			cos_fac = cosfactor(light->origin, i.point, i.objnode->\
				get_normal(i.point, light->origin, i.objnode->object));
			add_light_to_coeff(&i.coeff, light->color, cos_fac);
		}
		light = light->next;
	}
	i.color = apply_coeff(i.color, i.coeff);
	return (adjust_brightness(i.color, i.objnode->phong.diff).trgb);
}

int	specular_component(t_data *d, t_intrsct i, t_lightlst *light)
{
	float		cos_fac;
	float		specular;
	t_3d		l_to_p;
	t_3d		normal;

	if (!i.objnode->phong.spec)
		return (0);
	while (light)
	{
		if (!is_shadowed(light->origin, d->objectlist, i.point))
		{
			normal = i.objnode->get_normal(i.point,
					light->origin, i.objnode->object);
			l_to_p = norm(subtract(i.point, light->origin));
			cos_fac = cosfactor(i.ray.origin, i.point, reflect(l_to_p, normal));
			specular = pow(cos_fac, i.objnode->spec_exp);
			add_light_to_coeff(&i.coeff, light->color, specular);
		}
		light = light->next;
	}
	i.color = apply_coeff(i.color, i.coeff);
	return (adjust_brightness(i.color, i.objnode->phong.spec).trgb);
}

/* 

int	specular_component__(t_data *d, t_intrsct i, t_lightlst *light)
{
	if (!i.objnode->phong.spec)
		return (0);
	if (i.depth > RAYDEPTH)
		return (i.color.trgb);
	i.ray.origin = i.point;
	i.ray.direction = reflect(i.ray.direction,
			i.objnode->get_normal(i.point, i.ray.origin, i.objnode->object));
	i.color.trgb = trace_ray(d, i.ray, i.depth + 1);
	return (adjust_brightness(i.color, i.objnode->phong.spec).trgb);
} */
