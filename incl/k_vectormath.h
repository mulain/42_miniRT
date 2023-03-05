#ifndef VECTORMATH_H
# define VECTORMATH_H

// # include "../../incl/minirt.h"

# define WIDTH	1000
# define HEIGHT	1000

typedef struct s_data	t_data;

double		sqr(double n);
double		length_base(t_vector vec);
double		length_sqr(t_vector vec);
double		dot(t_vector v1, t_vector v2);
t_vector	cross(t_vector v1, t_vector v2);
t_vector	sum(t_vector v1, t_vector v2);
t_vector	extr(t_vector v1, t_vector v2);
t_vector	mult(t_vector v1, t_vector v2);
t_vector	divide(t_vector v1, t_vector v2);
t_vector	negative(t_vector v1);
void		equalize(t_vector *v1, t_vector v2);
void		ite_ray(t_data *data);
t_vector	scale_to(t_vector v, double f);
t_vector	norml(t_vector v);
t_vector	find_pixel_coord(double	x, double y, t_data *data);
void		vpr(t_vector v);
double		calc_plane(void *pl, t_vector d, t_data *data);
void		my_put_pixel(t_data *data, int x, int y, t_color color);
double		calc_sphere(void *sphere, t_vector d, t_data *data);

// calc_vector1.c
t_vector	point_add(t_vector p1, t_vector p2);
t_vector	point_subtract(t_vector p1, t_vector p2);
double		point_distance(t_vector p1, t_vector p2);
t_vector	vector_multiply(t_vector v, double mult);
t_vector	vector_divide(t_vector v, double div);

// calc_vector2.c
double		vector_length(t_vector v);
double		vector_dotprod(t_vector v1, t_vector v2);
t_vector	vector_crossprod(t_vector v1, t_vector v2);





#endif