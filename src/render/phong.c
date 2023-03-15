
#include "../incl/minirt.h"

int	ambient_component(t_data *d, t_intrsct i)
{
	double	brightness;

	if (!i.objnode->phong.amb)
		return (0);
	brightness = d->amb_light.brightness * i.objnode->phong.amb;
	return (direct_light(i.color, d->amb_light.color, brightness));
}

int	diffuse_component(t_data *d, t_intrsct i, t_lightlst *lightnode)
{
	double	cos_fac;
	t_3d	light_origin;

	if (!i.objnode->phong.diff)
		return (0);
	while (lightnode)
	{
		if (!is_shadowed(lightnode->light, d->objectlist, i.point))
		{
			light_origin = lightnode->light->origin;
			cos_fac = cosfactor(light_origin, i.point, i.objnode->\
				get_normal(i.point, light_origin, i.objnode->object));
			add_light_to_coeff(&i.coeff, lightnode->light->color, cos_fac);
		}
		lightnode = lightnode->next;
	}
	i.color = apply_coeff(i.color, i.coeff);
	return (adjust_brightness(i.color, i.objnode->phong.diff).trgb);
}

int	specular_component(t_data *d, t_intrsct i, t_lightlst *lightnode)
{
	float		cos_factor;
	float		specular;
	t_3d		light_to_point;
	t_3d		light_refl_dir;
	t_3d		view_dir;
	t_3d		local_normal;
	t_3d		light_origin;
	int			specular_exponent;

	specular_exponent = 1200; //2 to 1250
	if (!i.objnode->phong.spec)
		return (0);
	while (lightnode)
	{
		if (!is_shadowed(lightnode->light, d->objectlist, i.point))
		{
			light_origin = lightnode->light->origin;
			local_normal = i.objnode->get_normal(i.point, light_origin, i.objnode->object);
			light_to_point = norm(subtract(i.point, light_origin));
			light_refl_dir = reflect(light_to_point, local_normal);
			view_dir = norm(subtract(i.point, i.ray.origin));
			cos_factor = dot(light_refl_dir, view_dir);
			if (cos_factor < EPSILON)
				specular = 0;
			else
				specular = pow(cos_factor, specular_exponent);
			add_light_to_coeff(&i.coeff, lightnode->light->color, specular);
		}
		lightnode = lightnode->next;
	}
	i.color = apply_coeff(i.color, i.coeff);
	return (adjust_brightness(i.color, i.objnode->phong.spec).trgb);
}


/* vec3 specular(vec3 ks, vec3 Ls, vec3 R, vec3 V, float s) {
    float cos_theta = max(dot(R, V), 0.0);
    float specular_intensity = pow(cos_theta, s);
    return ks * Ls * specular_intensity;

int	specular_component__(t_data *d, t_intrsct i, t_lightlst *lightnode)
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
