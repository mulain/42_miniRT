# include "../incl/minirt.h"

void	print_objlist(t_objlist *lst)
{
	t_objlist	*temp;

	temp = lst;
	while (temp)
	{
		if (temp->objtype == sp)
			print_sphere(temp->content);
		else if (temp->objtype == pl)
			print_plane(temp->content);

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
	printf("  x: %f\n", d->camera.org.x);
	printf("  y: %f\n", d->camera.org.y);
	printf("  z: %f\n", d->camera.org.z);
	ft_printf("Normvector:\n");
	printf("  x: %f\n", d->camera.normvector.x);
	printf("  y: %f\n", d->camera.normvector.y);
	printf("  z: %f\n", d->camera.normvector.z);
	ft_printf("Field of view:\n");
	ft_printf("  %i degrees\n", d->camera.fov);
}

void	print_light(t_data *d)
{
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

void	print_plane(t_plane *pl)
{
	ft_printf("----- Plane -----\n");
	ft_printf("Coordinates:\n");
	printf("  x: %f\n", pl->anchr.x);
	printf("  y: %f\n", pl->anchr.y);
	printf("  z: %f\n", pl->anchr.z);

	ft_printf("Normvector:\n");
	printf("  x: %f\n", pl->orientation_vector.x);
	printf("  y: %f\n", pl->orientation_vector.y);
	printf("  z: %f\n", pl->orientation_vector.z);

	ft_printf("Color:\n");
	ft_printf("  r: %i\n", pl->color.r);
	ft_printf("  g: %i\n", pl->color.g);
	ft_printf("  b: %i\n", pl->color.b);
}