
#include "../incl/minirt.h"

void	diffuse(t_data *d, t_intrsct *i, t_light light)
{
	double	cos_fac;

	(void)d;
	cos_fac = cosfactor(light.origin, *i);
	if (cos_fac < EPSILON)
		cos_fac = 0;
	add_light(&i->coeff, light.color, cos_fac);
	//this just calculates how much ligth to add to obj
	//base color.
}

void	specular(t_data *d, t_intrsct *i, t_light light)
{
	i->depth++;
	if (i->depth < RAYDEPTH)
	{
		i->ray.origin = i->point;
		i->ray.direction = refract(i->ray.direction,
			i->objnode->get_normal(i->point, light.origin, i->objnode->object));
		i->color.trgb = trace_ray(d, d->lightlst, i->ray, i->depth);
	}
		/* && newintersection.object is reflecting
		test next reflection */
	//calculate new ray
	add_light(coeff, trace_ray(d, d->lightlst, i->ray, i->depth)

	//this should calculate how much light to add
	//to whatever the base color of the last hit object
	// is. next q: what is the base color of reflective objs?
}

/*
R = I - 2(I · N)N
*/
t_3d	refract(t_3d incoming, t_3d normal)
{
	double		dotprod;

	dotprod = dot(incoming, normal);
	return (subtract(incoming, scale(normal, 2 * dotprod)));
}