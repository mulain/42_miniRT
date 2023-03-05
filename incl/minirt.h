
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

// calc_color.c
t_color		adjust_brightness(t_color color, double factor);
t_color		mult_colors(t_color color1, t_color color2);
t_color		add_amblight(t_color base, t_ambientlight light);

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
int			trace_ray(t_data *d, t_ray ray);
//t_3d		pixel_to_point(t_data *d, int x, int y);
t_3d		get_vector(t_data *d, int x, int y);
t_intrsct	get_objintersect(t_objlist *objlist, t_ray ray);
t_color		add_shadow(t_data *d, t_objlist *objlist, t_intrsct i);
bool		is_shadowed(t_data *d, t_objlist *objlist, t_3d point);
void		render(t_data *d);

// hooks.c
int			key_release(int key, t_data *d);
int			event_windowdestroy(t_data *d);

// intersect_util.c
double		solve_quad(double a, double b, double c);

// intersect_2d.c
t_intrsct	intersect_plane(t_ray ray, void *obj);
t_intrsct	intersect_disc(t_ray ray, void *obj);
t_intrsct 	intersect_triangle(t_ray ray, void *obj);
bool	is_inside(t_3d p1, t_3d p2, t_3d p3, t_3d p_eval);

// intersect_3d.c
t_intrsct	intersect_sphere(t_ray ray, void *obj);
t_intrsct	intersect_cylinder(t_ray ray, void *obj);
t_intrsct	intersect_tube(t_ray ray, void *obj);

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
void		parse_triangle(t_data *d);

// parsing_utils.c
double		parse_double(t_data *d, char *input, char *msg);
t_color		parse_color(t_data *d, char *input, char *msg);
t_3d		parse_point(t_data *d, char *input, char *msg);
t_3d		parse_vector(t_data *d, char *input, char *msg);
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
