
#include "minirt.h"

void	put_pixel(t_data *d, int x, int y, int color)
{
	char	*pxl;

	pxl = d->img_addr + y * d->img_line_length + x * d->img_bytespp;
	*(unsigned int *)pxl = color;


}
