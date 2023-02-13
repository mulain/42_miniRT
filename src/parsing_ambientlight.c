# include "../incl/minirt.h"

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
		exit_free(d, E_AMBLIGHTDEF);
	d->amb_light.declared = true;
	d->parse.min = 0.0;
	d->parse.max = 1.0;
	parse_double(d, &d->amb_light.brightness, 1, E_AMBLIGHT1);
	parse_tcolor(d, &d->amb_light.color, 2, E_AMBLIGHT2);
	free_2d_char(d->parse.elmnts);
	d->parse.elmnts = NULL;
	print_ambientlight(d);
}
