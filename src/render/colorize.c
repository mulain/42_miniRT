
#include "../incl/minirt.h"

void	diffuse(t_rgb *coeff, t_light light, t_intrsct *i, t_ray ray)
{
	double	cos_fac;

	(void)ray;
	cos_fac = cosfactor(light.origin, *i);
	if (cos_fac < EPSILON)
		cos_fac = 0;
	add_light(coeff, light.color, cos_fac);
}
