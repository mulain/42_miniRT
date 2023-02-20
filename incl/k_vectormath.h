#ifndef VECTORMATH_H
# define VECTORMATH_H

// # include "../../incl/minirt.h"

# define WIDTH	1000
# define HEIGHT	1000
# define DEAPTH	500

// # define MIN_X	-100
// # define MIN_Y	-100
// # define MAX_X	100
// # define MAX_Y	100
// # define MAX_Z	0
// # define MIN_Z	-500

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
void		find_pixel_coord(double	x, double y, t_data *data);
void		vpr(t_vector v);




#endif