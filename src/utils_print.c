# include "../incl/minirt.h"

void	print_ambientlight(t_data *d)
{
	ft_printf("----- Ambient Light -----\n");
	ft_printf("Brightness:\n");
	printf("  %f\n", d->amb_light.brightness);
	ft_printf("Color:\n");
	ft_printf("  r: %i\n", d->amb_light.color.r);
	ft_printf("  g: %i\n", d->amb_light.color.g);
	ft_printf("  b: %i\n", d->amb_light.color.b);
}

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
