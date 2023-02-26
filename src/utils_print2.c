
#include "minirt.h"

void	print_sphere(t_sphere *sp)
{
	printf("----- Sphere -----\n");
	printf("Center:\n");
	printf("  x: %f\n", sp->center.x);
	printf("  y: %f\n", sp->center.y);
	printf("  z: %f\n", sp->center.z);
	printf("Radius:\n");
	printf("  %f\n", sp->radius);
	printf("Color:\n");
	printf("  r: %i\n", sp->color.r);
	printf("  g: %i\n", sp->color.g);
	printf("  b: %i\n", sp->color.b);
}

void	print_plane(t_plane *pl)
{
	printf("----- Plane -----\n");
	printf("Point:\n");
	printf("  x: %f\n", pl->point.x);
	printf("  y: %f\n", pl->point.y);
	printf("  z: %f\n", pl->point.z);
	printf("Vector:\n");
	printf("  x: %f\n", pl->vector.x);
	printf("  y: %f\n", pl->vector.y);
	printf("  z: %f\n", pl->vector.z);
	printf("Color:\n");
	printf("  r: %i\n", pl->color.r);
	printf("  g: %i\n", pl->color.g);
	printf("  b: %i\n", pl->color.b);
}

void	print_cylinder(t_cylinder *cy)
{
	printf("----- Cylinder -----\n");
	printf("Base:\n");
	printf("  x: %f\n", cy->center.x);
	printf("  y: %f\n", cy->center.y);
	printf("  z: %f\n", cy->center.z);
	printf("Axis:\n");
	printf("  x: %f\n", cy->axis.x);
	printf("  y: %f\n", cy->axis.y);
	printf("  z: %f\n", cy->axis.z);
	printf("Radius:\n");
	printf("  %f\n", cy->radius);
	printf("Height:\n");
	printf("  %f\n", cy->height);
	printf("Color:\n");
	printf("  r: %i\n", cy->color.r);
	printf("  g: %i\n", cy->color.g);
	printf("  b: %i\n", cy->color.b);
}

void	print_t3d(t_3d v, char *name)
{
	if (name)
		printf("Name: %s\n", name);
	else
		printf("Vector:\n");
	printf("  x: %f\n", v.x);
	printf("  y: %f\n", v.y);
	printf("  z: %f\n", v.z);
}
