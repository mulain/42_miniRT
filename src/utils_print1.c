
#include "../incl/minirt.h"

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
		else if (temp->objtype == cy)
			print_cylinder(temp->content);
		temp = temp->next;
	}
}

void	print_ambientlight(t_data *d)
{
	printf("----- Ambient Light -----\n");
	printf("Brightness:\n");
	printf("  %f\n", d->amb_light.brightness);
	printf("Color:\n");
	printf("  r: %i\n", d->amb_light.color.r);
	printf("  g: %i\n", d->amb_light.color.g);
	printf("  b: %i\n", d->amb_light.color.b);
}

void	print_camera(t_data *d)
{
	printf("----- Camera -----\n");
	printf("Viewpoint:\n");
	printf("  x: %f\n", d->camera.viewpoint.x);
	printf("  y: %f\n", d->camera.viewpoint.y);
	printf("  z: %f\n", d->camera.viewpoint.z);
	printf("Normvector:\n");
	printf("  x: %f\n", d->camera.normvector.x);
	printf("  y: %f\n", d->camera.normvector.y);
	printf("  z: %f\n", d->camera.normvector.z);
	printf("Field of view:\n");
	printf("  %i degrees\n", d->camera.fieldofview);
}

void	print_light(t_data *d)
{
	if (!d->light.declared)
	{
		printf("Light not declared.\n");
		return ;
	}
	printf("----- Light -----\n");
	printf("Coordinates:\n");
	printf("  x: %f\n", d->light.coordinates.x);
	printf("  y: %f\n", d->light.coordinates.y);
	printf("  z: %f\n", d->light.coordinates.z);
	printf("Brightness:\n");
	printf("  %f\n", d->light.brightness);
	printf("Color:\n");
	printf("  r: %i\n", d->light.color.r);
	printf("  g: %i\n", d->light.color.g);
	printf("  b: %i\n", d->light.color.b);
}
