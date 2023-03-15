
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
	t_3d	light_origin;

	if (!i.objnode->phong.diff)
		return (0);
	while (light)
	{
		if (!is_shadowed(light->origin, d->objectlist, i.point))
		{
			light_origin = light->origin;
			cos_fac = cosfactor(light_origin, i.point, i.objnode->\
				get_normal(i.point, light_origin, i.objnode->object));
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
	int			specular_exponent;

	specular_exponent = 20; //2 to 1250 highlight size
	if (!i.objnode->phong.spec)
		return (0);
	while (light)
	{
		if (!is_shadowed(light->origin, d->objectlist, i.point))
		{
			normal = i.objnode->get_normal(i.point, light->origin, i.objnode->object);
			l_to_p = norm(subtract(i.point, light->origin));
			cos_fac = cosfactor(i.ray.origin, i.point, reflect(l_to_p, normal));
			specular = pow(cos_fac, specular_exponent);
			add_light_to_coeff(&i.coeff, light->color, specular);
		}
		light = light->next;
	}
	i.color = apply_coeff(i.color, i.coeff);
	return (adjust_brightness(i.color, i.objnode->phong.spec).trgb);
}


/* vec3 specular(vec3 ks, vec3 Ls, vec3 R, vec3 V, float s) {
    float cos_theta = max(dot(R, V), 0.0);
    float specular_intensity = pow(cos_theta, s);
    return ks * Ls * specular_intensity;

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