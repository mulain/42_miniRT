#include "libft/include/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>

/* int main()
{
	char* string1 = " start 	s justspacebeforethis	justtabbeforethis 	 	spaceandtabmixed end	";
	char* string2 = "     ";
	char** out;

	out = split_multichar(string2, " \t");
	if (out)
		for (int i = 0; out[i]; i++)
			printf("string %i:'%s'\n", i, out[i]);
	free_2d_char(out);

	out = ft_split(string2, ' ');
	printf("out:%p\n", out);
	printf("out[0]:%p\n", out[0]);
	if (out)
		for (int i = 0; out[i]; i++)
			printf("string %i:'%s'\n", i, out[i]);

} */

typedef struct {
    double x, y, z;
} Vector3;

typedef struct {
    Vector3 center;
    double radius;
    double height;
} Cylinder;

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

int intersectCylinder(const Ray* ray, const Cylinder* cylinder, double* t)
{
    Vector3 oc = {ray->origin.x - cylinder->center.x, ray->origin.y - cylinder->center.y, ray->origin.z - cylinder->center.z};
    double a = ray->direction.x * ray->direction.x + ray->direction.z * ray->direction.z;
    double b = 2.0 * (oc.x * ray->direction.x + oc.z * ray->direction.z);
    double c = oc.x * oc.x + oc.z * oc.z - cylinder->radius * cylinder->radius;
    double discr = b * b - 4.0 * a * c;
    if (discr < 0)
		return (INFINITY); // no intersection
    double t0 = (-b - sqrt(discr)) / (2.0 * a);
    double t1 = (-b + sqrt(discr)) / (2.0 * a);
    if (t0 > t1)
	{
        double temp = t0;
        t0 = t1;
        t1 = temp;
    }
    if (t1 < 0.0)
	{
        return 0;
    }
    double y0 = ray->origin.y + t0 * ray->direction.y;
    double y1 = ray->origin.y + t1 * ray->direction.y;
    double ymin = cylinder->center.y - 0.5 * cylinder->height;
    double ymax = cylinder->center.y + 0.5 * cylinder->height;
    if ((y0 < ymin && y1 < ymin) || (y0 > ymax && y1 > ymax))
	{
        return 0;
    }
    if (y0 < ymin)
	{
        t0 = (ymin - ray->origin.y) / ray->direction.y;
    }
	else if (y0 > ymax)
	{
        t0 = (ymax - ray->origin.y) / ray->direction.y;
    }
    if (y1 < ymin)
	{
        t1 = (ymin - ray->origin.y) / ray->direction.y;
    }
	else if (y1 > ymax)
	{
        t1 = (ymax - ray->origin.y) / ray->direction.y;
    }
    if (t0 > t1) {
        return 0;
    }
    if (t0 < 0.0) {
        t0 = t1;
        if (t0 < 0.0) {
            return 0;
        }
    }
    *t = t0;
    return 1;
}

int	main()
{
    Cylinder cylinder = {{0.0, 0.0, 0.0}, 1.0, 2.0};
    Ray ray = {{0.0, 2.0, 0.0}, {0.0, -1.0, 0.0}};
    double t;
    if (intersectCylinder(&ray, &cylinder, &t)) {
        printf("Intersection at t = %lf\n", t);
    } else {
        printf("No intersection\n");
    }
    return 0;
}