# include "../incl/minirt.h"

void	print_objlist(t_objlist *lst)
{
	t_objlist	*temp;

	temp = lst;
	while (temp)
	{
		if (temp->objtype == sp)
			print_sphere(temp->content);
		temp = temp->next;
	}
}

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

void	print_light(t_data *d)
{
	if (!d->light.declared)
	{
		ft_printf("Light not declared.\n");
		return ;
	}
	ft_printf("----- Light -----\n");
	ft_printf("Coordinates:\n");
	printf("  x: %f\n", d->light.coordinates.x);
	printf("  y: %f\n", d->light.coordinates.y);
	printf("  z: %f\n", d->light.coordinates.z);
	ft_printf("Brightness:\n");
	printf("  %f\n", d->light.brightness);
	ft_printf("Color:\n");
	ft_printf("  r: %i\n", d->light.color.r);
	ft_printf("  g: %i\n", d->light.color.g);
	ft_printf("  b: %i\n", d->light.color.b);
}

void	print_sphere(t_sphere *sp)
{
	ft_printf("----- Sphere -----\n");
	ft_printf("Coordinates:\n");
	printf("  x: %f\n", sp->center.x);
	printf("  y: %f\n", sp->center.x);
	printf("  z: %f\n", sp->center.x);
	ft_printf("Diameter:\n");
	printf("  %f\n", sp->diameter);
	ft_printf("Color:\n");
	ft_printf("  r: %i\n", sp->color.r);
	ft_printf("  g: %i\n", sp->color.g);
	ft_printf("  b: %i\n", sp->color.b);
}