# include "../incl/minirt.h"

void	shutdown(t_data *d)
{
	if (d->line)
		free(d->line);
	free_2d_char(d->elements_a);
	free_2d_char(d->elements_b);
}
