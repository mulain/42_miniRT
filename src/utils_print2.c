# include "../incl/minirt.h"

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
	ft_printf("Anchor:\n");
	printf("  x: %f\n", pl->anchor.x);
	printf("  y: %f\n", pl->anchor.y);
	printf("  z: %f\n", pl->anchor.z);
	ft_printf("Normvector:\n");
	printf("  x: %f\n", pl->normvector.x);
	printf("  y: %f\n", pl->normvector.y);
	printf("  z: %f\n", pl->normvector.z);
	ft_printf("Color:\n");
	ft_printf("  r: %i\n", pl->color.r);
	ft_printf("  g: %i\n", pl->color.g);
	ft_printf("  b: %i\n", pl->color.b);
}

void	print_cylinder(t_cylinder *cy)
{
	ft_printf("----- Cylinder -----\n");
	ft_printf("Anchor:\n");
	printf("  x: %f\n", cy->anchor.x);
	printf("  y: %f\n", cy->anchor.y);
	printf("  z: %f\n", cy->anchor.z);
	ft_printf("Normvector:\n");
	printf("  x: %f\n", cy->normvector.x);
	printf("  y: %f\n", cy->normvector.y);
	printf("  z: %f\n", cy->normvector.z);
	ft_printf("Diameter:\n");
	printf("  %f\n", cy->diameter);
	ft_printf("Height:\n");
	printf("  %f\n", cy->height);
	ft_printf("Color:\n");
	ft_printf("  r: %i\n", cy->color.r);
	ft_printf("  g: %i\n", cy->color.g);
	ft_printf("  b: %i\n", cy->color.b);
}
