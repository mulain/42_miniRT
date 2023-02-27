
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
t_intrsct	intersect_plane(t_ray ray, t_plane plane);
t_intrsct	intersect_sphere(t_ray ray, t_sphere sphere);
t_intrsct	intersect_cylinder(t_ray ray, t_cylinder cylinder);

// calc_vector1.c
t_3d		add(t_3d p1, t_3d p2);
t_3d		subtract(t_3d p1, t_3d p2);
double		distance(t_3d p1, t_3d p2);
t_3d		mult(t_3d v, double mult);
t_3d		divide(t_3d v, double div);

// calc_vector2.c
double		length(t_3d v);
double		dot(t_3d v1, t_3d v2);
t_3d		cross(t_3d v1, t_3d v2);
t_3d		norm(t_3d v);

// draw.c
void		put_pixel(t_mlx *mlx, int x, int y, int color);
t_3d		pixel_to_point(t_data *d, int x, int y);
t_3d		get_3d(t_data *d, int x, int y);
void		render(t_data *d);

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
t_3d		parse_tpoint(t_data *d, char *input, char *msg);
t_3d		parse_tvector(t_data *d, char *input, char *msg);
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
void		print_3d(t_3d p, char *name);
void		print_3d(t_3d v, char *name);

// shutdown.c
void		error_exit(t_data *d, char *msg);
void		free_all(t_data *d);

#endif
