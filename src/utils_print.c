# include "../incl/minirt.h"

void	print_camera(t_data *d)
{
	ft_printf("----- Camera -----\n");
	ft_printf("Viewpoint:\n");
	printf("  x: %f\n", d->camera.viewpoint.x);
	printf("  y: %f\n", d->camera.viewpoint.y);
	printf("  z: %f\n", d->camera.viewpoint.z);
	ft_printf("Normvector:\n");
	printf("  x: %f\n", d->camera.normvector.x);
	printf("  y: %f\n", d->camera.normvector.y);
	printf("  z: %f\n", d->camera.normvector.z);
	ft_printf("Field of view:\n");
	ft_printf("  %i degrees\n", d->camera.fieldofview);
}
