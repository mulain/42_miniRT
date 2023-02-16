
#include "../incl/minirt.h"

void	print_sphere(t_sphere *sp)
{
	printf("----- Sphere -----\n");
	printf("Coordinates:\n");
	printf("  x: %f\n", sp->center.x);
	printf("  y: %f\n", sp->center.x);
	printf("  z: %f\n", sp->center.x);
	printf("Diameter:\n");
	printf("  %f\n", sp->diameter);
	printf("Color:\n");
	printf("  r: %i\n", sp->color.r);
	printf("  g: %i\n", sp->color.g);
	printf("  b: %i\n", sp->color.b);
}

void	print_plane(t_plane *pl)
{
	printf("----- Plane -----\n");
	printf("Anchor:\n");
	printf("  x: %f\n", pl->anchor.x);
	printf("  y: %f\n", pl->anchor.y);
	printf("  z: %f\n", pl->anchor.z);
	printf("Normvector:\n");
	printf("  x: %f\n", pl->normvector.x);
	printf("  y: %f\n", pl->normvector.y);
	printf("  z: %f\n", pl->normvector.z);
	printf("Color:\n");
	printf("  r: %i\n", pl->color.r);
	printf("  g: %i\n", pl->color.g);
	printf("  b: %i\n", pl->color.b);
}

void	print_cylinder(t_cylinder *cy)
{
	printf("----- Cylinder -----\n");
	printf("Anchor:\n");
	printf("  x: %f\n", cy->anchor.x);
	printf("  y: %f\n", cy->anchor.y);
	printf("  z: %f\n", cy->anchor.z);
	printf("Normvector:\n");
	printf("  x: %f\n", cy->normvector.x);
	printf("  y: %f\n", cy->normvector.y);
	printf("  z: %f\n", cy->normvector.z);
	printf("Diameter:\n");
	printf("  %f\n", cy->diameter);
	printf("Height:\n");
	printf("  %f\n", cy->height);
	printf("Color:\n");
	printf("  r: %i\n", cy->color.r);
	printf("  g: %i\n", cy->color.g);
	printf("  b: %i\n", cy->color.b);
}
