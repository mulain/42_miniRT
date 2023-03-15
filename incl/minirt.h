
#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include <pthread.h>

# include "mlx.h"
# include "../libft/include/libft.h"
# include "structs.h"
# include "list_obj.h"
# include "list_light.h"
# include "defines.h"

// main.c
int			main(int argc, char **argv);
void		get_infile(t_data *d, int argc, char **argv);
void		init_structs(t_data *d);
void		init_mlx(t_data *d);
void		manage_threads(t_data *d);

// INTERSECT

// intersect_2d.c
t_intrsct	intersect_plane(t_ray ray, void *obj);
t_intrsct	intersect_disc(t_ray ray, void *obj);
t_intrsct 	intersect_triangle(t_ray ray, void *obj);
bool		is_left(t_3d point, t_3d normal, t_3d vertex1, t_3d vertex2);

// intersect_3d.c
t_intrsct	intersect_sphere(t_ray ray, void *obj);
t_intrsct	intersect_tube(t_ray ray, void *obj);
t_intrsct	intersect_cone(t_ray ray, void *obj);
t_intrsct	intersect_cone2(t_intrsct i, t_ray ray, t_cone *cone, double *t);

// intersect_util.c
double		solve_quad(double a, double b, double c, double *t);
t_3d		translate(t_3d obj_axis, t_3d ray_dir);
bool		is_withinbounds(t_3d point, t_3d ref, t_3d axis, double height);
double		to_deg(double radians);
double		to_rad(double degrees);

// LISTS -> have seperate headers

// PARSE

// parse_2d.c
void		parse_plane(t_data *d);
void		parse_disc(t_data *d);
void		parse_triangle(t_data *d);

// parse_3d.c
void		parse_sphere(t_data *d);
void		parse_cylinder(t_data *d);
void		parse_cone(t_data *d);

// parse_lights_cam.c
void		parse_ambientlight(t_data *d);
void		parse_camera(t_data *d);
void		parse_light(t_data *d);

// parse_utils1.c
double		parse_double(t_data *d, char *input, char *msg);
t_color		parse_color(t_data *d, char *input, char *msg);
t_3d		parse_point(t_data *d, char *input, char *msg);
t_3d		parse_vector(t_data *d, char *input, char *msg);
int			parse_int(t_data *d, char *input, char *msg);

// parse_utils2.c
t_phong		parse_phong(t_data *d, char *input, char *msg);

// parse.c
void		parse(t_data *d);
char		*gnl_trimmed(int fd);
void		parse_line(t_data *d, char *line);

// RENDER

// light_operations.c
void		add_light_to_coeff(t_rgb *coeff, t_color lightcolor,
				double brightness);
t_color		apply_coeff(t_color color, t_rgb rgb_coeff);
int			add_colors(int color1, int color2, int color3);
int			direct_light(t_color objcolor, t_color lightcolor,
				double brightness);
t_color		adjust_brightness(t_color color, double brightness);

// phong.c
int			ambient_component(t_data *d, t_intrsct i);
int			diffuse_component(t_data *d, t_intrsct i, t_lightlst *lightnode);
int			specular_component(t_data *d, t_intrsct i, t_lightlst *lightnode);

// render.c
void		*render_threads(void *ptr);
void		render(t_data *d);
t_3d		get_vector(t_data *d, int x, int y);
int			trace_ray(t_data *d, t_ray ray, int depth);
t_intrsct	get_objintersect(t_objlst *objnode, t_ray ray);

// utils.c
void		put_pixel(t_mlx *mlx, int x, int y, int color);
bool		is_shadowed(t_light *light, t_objlst *objnode, t_3d point);
double		cosfactor(t_3d ray_origin, t_3d hitpoint, t_3d surface_normal);
t_3d		reflect(t_3d incoming, t_3d normal);

// SURFACE_NORMAL

// get_normal_2d.c
t_3d		normal_plane(t_3d point, t_3d ray_origin, void *obj);
t_3d		normal_disc(t_3d point, t_3d ray_origin, void *obj);
t_3d		normal_triangle(t_3d point, t_3d ray_origin, void *obj);

// get_normal_3d.c
t_3d		normal_sphere(t_3d point, t_3d ray_origin, void *obj);
t_3d		normal_tube(t_3d point, t_3d ray_origin, void *obj);
t_3d		normal_cone(t_3d point, t_3d ray_origin, void *obj);

// UTILS

// calculate1.c
t_3d		add(t_3d p1, t_3d p2);
t_3d		subtract(t_3d p1, t_3d p2);
t_3d		scale(t_3d v, double mult);
t_3d		reverse(t_3d v);

// calculate2.c
double		dot(t_3d v1, t_3d v2);
t_3d		cross(t_3d v1, t_3d v2);
t_3d		norm(t_3d v);
double		length(t_3d v);
double		distance(t_3d p1, t_3d p2);

// hooks.c
int			key_release(int key, t_data *d);
int			event_windowdestroy(t_data *d);

// print1.c
void		print_objlst(t_objlst *lst);
void		print_ambientlight(t_data *d);
void		print_camera(t_data *d);
void		print_light(t_data *d);

// print2.c
void		print_sphere(t_sphere *sp);
void		print_plane(t_plane *pl);
void		print_tube(t_tube *tu);
void		print_3d(t_3d p, char *name);
void		print_3d(t_3d v, char *name);

// shutdown.c
void		error_exit(t_data *d, char *msg);
void		free_all(t_data *d);

#endif
