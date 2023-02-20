
# include "../incl/minirt.h"

void	vpr(t_vector v)
{
	printf("x = %lf\n", v.x);
	printf("y = %lf\n", v.y);
	printf("z = %lf\n", v.z);
	printf("_______\n");
	printf("\n");

}

double	sqr(double n)
{
	return (n * n);
}

double	length_base(t_vector vec)
{
	double ret;

	ret = sqr(vec.x) + sqr(vec.y) + sqr(vec.z);
	////printf("length_base = %lf\n", ret);
	return (ret);
}

double	length_sqr(t_vector vec)
{
	////printf("length_sqr = %lf\n", sqr(length_base(vec)));
	return (sqr(length_base(vec)));
}

double	dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	cross(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	if (ret.x == -0.0)
		ret.x = (double) +0.0;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	if (ret.y == -0.0)
		ret.y = (double) +0.0;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	if (ret.z == -0.0)
		ret.z = (double) +0.0;

	//printf("cross \n");
	//vpr(ret);

	return (ret);
}

t_vector	sum(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;

	return (ret);
}

t_vector	extr(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

t_vector	mult(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;
	ret.z = v1.z * v2.z;
	return (ret);
}

t_vector	divide(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.x / v2.x;
	ret.y = v1.y / v2.y;
	ret.z = v1.z / v2.z;
	return (ret);
}

t_vector	negative(t_vector v1)
{
	t_vector	ret;

	ret.x = -v1.x;
	ret.y = -v1.y;
	ret.z = -v1.z;
	return (ret);
}

void	equalize(t_vector *v1, t_vector v2)
{
	v1->x = v2.x;
	v1->y = v2.y;
	v1->z = v2.z;
}


t_vector	scale_to(t_vector v, double f)
{
	t_vector	ret;

	//printf("f = %lf\n", f);
	ret.x = f * v.x;
	//printf("x sclaled = %lf\n", ret.x);
	ret.y = f * v.y;
	ret.z = f * v.z;
	//printf("scale to = \n");
	////vpr(ret);
	return(ret);
}

t_vector	norml(t_vector v)
{
	t_vector	ret;

	ret = scale_to(v, 1 / length_sqr(v));
	//printf("norml \n");
	// //printf("%lf", 1 / length_sqr(v));
	//vpr(v);
	//vpr(ret);
	return(ret);
}

t_vector	retr(t_vector v)
{
	t_vector	ret;

	ret.x = v.x;
	ret.y = v.y;
	ret.z = v.z;
	return (ret);

}






