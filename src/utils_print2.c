
#include "minirt.h"

void	print_sphere(t_sphere *sphere)
{
	printf("----- Sphere -----\n");
	printf("Center:\n");
	printf("  x: %f\n", sphere->center.x);
	printf("  y: %f\n", sphere->center.y);
	printf("  z: %f\n", sphere->center.z);
	printf("Radius:\n");
	printf("  %f\n", sphere->radius);
	printf("Color:\n");
	printf("  r: %i\n", sphere->color.r);
	printf("  g: %i\n", sphere->color.g);
	printf("  b: %i\n", sphere->color.b);
}

void	print_plane(t_plane *plane)
{
	printf("----- Plane -----\n");
	printf("Point:\n");
	printf("  x: %f\n", plane->point.x);
	printf("  y: %f\n", plane->point.y);
	printf("  z: %f\n", plane->point.z);
	printf("Vector:\n");
	printf("  x: %f\n", plane->vector.x);
	printf("  y: %f\n", plane->vector.y);
	printf("  z: %f\n", plane->vector.z);
	printf("Color:\n");
	printf("  r: %i\n", plane->color.r);
	printf("  g: %i\n", plane->color.g);
	printf("  b: %i\n", plane->color.b);
}

void	print_cylinder(t_cylinder *cylinder)
{
	printf("----- Cylinder -----\n");
	printf("Base:\n");
	printf("  x: %f\n", cylinder->base.x);
	printf("  y: %f\n", cylinder->base.y);
	printf("  z: %f\n", cylinder->base.z);
	printf("Axis:\n");
	printf("  x: %f\n", cylinder->axis.x);
	printf("  y: %f\n", cylinder->axis.y);
	printf("  z: %f\n", cylinder->axis.z);
	printf("Radius:\n");
	printf("  %f\n", cylinder->radius);
	printf("Height:\n");
	printf("  %f\n", cylinder->height);
	printf("Color:\n");
	printf("  r: %i\n", cylinder->color.r);
	printf("  g: %i\n", cylinder->color.g);
	printf("  b: %i\n", cylinder->color.b);
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
