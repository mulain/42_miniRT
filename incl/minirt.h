
#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>

//# include "../mlx/mlx.h"
# include "../libft/include/libft.h"
# include "structs.h"
# include "objlist.h"
# include "defines.h"

// calc_intersection.c
double		intersect_plane(t_ray ray, t_plane plane);


// calc_vector1.c
t_vector	point_add(t_point p1, t_point p2);
t_vector	point_subtract(t_point p1, t_point p2);
double	point_distance(t_point p1, t_point p2);
t_vector	vector_multiply(t_vector v, double mult);
t_vector	vector_divide(t_vector v, double div);

// calc_vector2.c
double		vector_length(t_vector vec);
double		vector_dotprod(t_vector v1, t_vector v2);
t_vector	vector_crossprod(t_vector v1, t_vector v2);

// main.c
void		get_infile(t_data *d, int argc, char **argv);
void		init_structs(t_data *d);
void		init_mlx(t_data *d);

// parsing.c
void		parsing(t_data *d);
char		*gnl_trimmed(int fd);
void		parse_line(t_data *d, char *line);

// parsing_lightsandcam.c
void		parse_ambientlight(t_data *d);
void		parse_camera(t_data *d);
void		parse_light(t_data *d);

// parsing_objects.c
void		parse_sphere(t_data *d);
void		parse_plane(t_data *d);
void		parse_cylinder(t_data *d);

// parsing_utils.c
void		parse_double(t_data *d, double *target, int index, char *msg);
void		parse_tcolor(t_data *d, t_color *color, int index, char *msg);
void		parse_tpoint(t_data *d, t_point *point, int index, char *msg);
void		parse_tvector(t_data *d, t_vector *vec, int index, char *msg);
void		parse_int(t_data *d, int *target, int index, char *msg);

// utils_print1.c
void		print_objlist(t_objlist *lst);
void		print_ambientlight(t_data *d);
void		print_camera(t_data *d);
void		print_light(t_data *d);

// utils_print2.c
void		print_sphere(t_sphere *sp);
void		print_plane(t_plane *pl);
void		print_cylinder(t_cylinder *cy);
void		print_point(t_point p, char *name);
void		print_vector(t_vector v, char *name);

// shutdown.c
void		error_exit(t_data *d, char *msg);
void		free_all(t_data *d);

#endif
