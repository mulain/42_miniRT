
#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>

# include "mlx.h"
# include "../libft/include/libft.h"
# include "structs.h"
# include "objlist.h"
# include "defines.h"

// calc_intersection.c
double		intersect_plane(t_ray ray, t_plane plane);
double		intersect_sphere(t_ray ray, t_sphere sphere);
double		intersect_cylinder(t_ray ray, t_cylinder cylinder);

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
t_vector	vector_normalize(t_vector v);

// hooks.c
int			key_release(int key, t_data *d);
int			event_windowdestroy(t_data *d);

// main.c
int			main(int argc, char **argv);
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
double		parse_double(t_data *d, char *input, char *msg);
t_color		parse_tcolor(t_data *d, char *input, char *msg);
t_vector	parse_tpoint(t_data *d, char *input, char *msg);
t_vector	parse_tvector(t_data *d, char *input, char *msg);
int			parse_int(t_data *d, char *input, char *msg);

// utils_print1.c
void		print_objlist(t_objlist *lst);
void		print_ambientlight(t_data *d);
void		print_camera(t_data *d);
void		print_light(t_data *d);

// utils_print2.c
void		print_sphere(t_sphere *sp);
void		print_plane(t_plane *pl);
void		print_cylinder(t_cylinder *cy);
void		print_vector(t_vector p, char *name);
void		print_vector(t_vector v, char *name);

// shutdown.c
void		error_exit(t_data *d, char *msg);
void		free_all(t_data *d);

#endif
