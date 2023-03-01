
#include "../incl/minirt.h"

double	solve_quad(double a, double b, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = b * b - 4 * a * c;
	if (discriminant < EPSILON)
		return (INFINITY);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 < EPSILON)
	{
		if (t2 < EPSILON)
			return (INFINITY);
		return (t2);
	}
	return (t1);
}
