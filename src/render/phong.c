
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

	if (!i.objnode->phong.diff)
		return (0);
	while (lightnode)
	{
		if (!is_shadowed(lightnode->light, d->objectlist, i.point))
		{
			cos_fac = cosfactor(lightnode->light->origin, i);
			add_light_to_coeff(&i.coeff, lightnode->light->color, cos_fac);
		}
		lightnode = lightnode->next;
	}
	i.color = apply_coeff(i.color, i.coeff);
	return (adjust_brightness(i.color, i.objnode->phong.diff).trgb);
}

int	specular_component(t_data *d, t_intrsct i)
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
}

/* void	specular(t_data *d, t_intrsct *i, t_light light)
{
	i->depth++;
	if (i->depth < RAYDEPTH)
	{
		i->ray.origin = i->point;
		i->ray.direction = reflect(i->ray.direction,
			i->objnode->get_normal(i->point, light.origin, i->objnode->object));
		i->color.trgb = trace_ray(d, d->lightlst, i->ray, i->depth);
	}
		/&& newintersection.object is reflecting
		test next reflection
	//calculate new ray
	add_light_to_coeff(coeff, trace_ray(d, d->lightlst, i->ray, i->depth)

	//this should calculate how much light to add
	//to whatever the base color of the last hit object
	// is. next q: what is the base color of reflective objs?
} */
