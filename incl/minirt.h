
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
# include "list_obj.h"
# include "list_light.h"
# include "defines.h"

// calc_vector1.c
t_3d		add(t_3d p1, t_3d p2);
t_3d		subtract(t_3d p1, t_3d p2);
t_3d		scale(t_3d v, double mult);
t_3d		reverse(t_3d v);

// calc_vector2.c
double		dot(t_3d v1, t_3d v2);
t_3d		cross(t_3d v1, t_3d v2);
t_3d		norm(t_3d v);
double		length(t_3d v);
double		distance(t_3d p1, t_3d p2);

// get_normal_2d.c
t_3d		get_normal_plane(t_3d point, void *obj);
t_3d		get_normal_disc(t_3d point, void *obj);
t_3d		get_normal_triangle(t_3d point, void *obj);

// get_normal_3d.c
t_3d		get_normal_sphere(t_3d point, void *obj);
t_3d		get_normal_tube(t_3d point, void *obj);
t_3d		get_normal_cone(t_3d point, void *obj);

// hooks.c
int			key_release(int key, t_data *d);
int			event_windowdestroy(t_data *d);

// intersect_util.c
double		solve_quad(double a, double b, double c);
t_3d		translate(t_3d obj_axis, t_3d ray_dir);
double		to_deg(double radians);
double		to_rad(double degrees);

// intersect_2d.c
t_intrsct	intersect_plane(t_ray ray, void *obj);
t_intrsct	intersect_disc(t_ray ray, void *obj);
t_intrsct 	intersect_triangle(t_ray ray, void *obj);
bool		is_inside(t_3d p1, t_3d p2, t_3d p3, t_3d p_eval);

// intersect_3d.c
t_intrsct	intersect_sphere(t_ray ray, void *obj);
t_intrsct	intersect_tube(t_ray ray, void *obj);
t_intrsct	intersect_cone(t_ray ray, void *obj);

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

// parsing_2d.c
void		parse_plane(t_data *d);
void		parse_disc(t_data *d);
void		parse_triangle(t_data *d);

// parsing_3d.c
void		parse_sphere(t_data *d);
void		parse_cylinder(t_data *d);
void		parse_cone(t_data *d);

// parsing_utils.c
double		parse_double(t_data *d, char *input, char *msg);
t_color		parse_color(t_data *d, char *input, char *msg);
t_3d		parse_point(t_data *d, char *input, char *msg);
t_3d		parse_vector(t_data *d, char *input, char *msg);
int			parse_int(t_data *d, char *input, char *msg);

// render.c
void		render(t_data *d);
t_3d		get_vector(t_data *d, int x, int y);
int			trace_ray(t_data *d, t_lightlst *lightnode, t_ray ray);
t_intrsct	get_objintersect(t_objlst *objnode, t_ray ray);
bool		is_shadowed(t_light *light, t_objlst *objnode, t_3d point);

// render_utils1.c
void		put_pixel(t_mlx *mlx, int x, int y, int color);
double		cosfactor(t_3d light_origin, t_intrsct i);
double		bright_diffuse(t_light light, t_intrsct i);

// render_utils2.c
void		add_lighttocoeff(t_rgb *coeff, t_color color, double brightness);
int			apply_coeff(t_color color, t_rgb rgb_coeff);
t_color		apply_brightness(t_color color, double factor);

// utils_print1.c
void		print_objlst(t_objlst *lst);
void		print_ambientlight(t_data *d);
void		print_camera(t_data *d);
void		print_light(t_data *d);

// utils_print2.c
void		print_sphere(t_sphere *sp);
void		print_plane(t_plane *pl);
void		print_tube(t_tube *tu);
void		print_3d(t_3d p, char *name);
void		print_3d(t_3d v, char *name);

// shutdown.c
void		error_exit(t_data *d, char *msg);
void		free_all(t_data *d);

#endif
