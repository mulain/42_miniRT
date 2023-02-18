
#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>

# include "../miniLibX/mlx.h"
# include "../libft/include/libft.h"
# include "structs.h"
# include "objlist.h"
# include "defines.h"
# include "../incl/k_vectormath.h"



// main.c
void	init_structs(t_data *d);
void	init_mlx(t_data *d);

// parsing.c
void	parsing(t_data *d, int argc, char **argv);
char	*gnl_trimmed(int fd);
void	parse_line(t_data *d, char *line);

// parsing_ambientlight.c
void	parse_ambientlight(t_data *d, char **elements);
void	check_amblight_declared(t_data *d, char **elements);
void	set_amblight_brightness(t_data *d, char **elements);
void	set_amblight_color(t_data *d, char **elements);

// parsing_camera.c
void	parse_camera(t_data *d, char **elements);
void	check_camera_declared(t_data *d, char **elements);
void	set_camera_viewpoint(t_data *d, char **elements);
void	set_camera_normvector(t_data *d, char **elements);
void	set_camera_fieldofview(t_data *d, char **elements);

// parsing_light.c
void	parse_light(t_data *d, char **elements);
void	check_light_declared(t_data *d, char **elements);
void	set_light_coordinates(t_data *d, char **elements);
void	set_light_brightness(t_data *d, char **elements);
void	set_light_color(t_data *d, char **elements);

// parsing_sphere.c
void	parse_sphere(t_data *d, char **elements);
void	set_sphere_center(t_data *d, t_sphere *sphere, char **elements);
void	set_sphere_diameter(t_data *d, t_sphere *sphere, char **elements);
void	set_sphere_color(t_data *d, t_sphere *sphere, char **elements);

// utils_is.c
bool	is_whitespace(char c);
bool	is_onlydigits(char *str);
bool	is_decimalformat(char *input);
bool	is_ucharformat(char *input);

// utils_print1.c
void	print_objlist(t_objlist *lst);
void	print_ambientlight(t_data *d);
void	print_camera(t_data *d);
void	print_light(t_data *d);
void	print_sphere(t_sphere *sp);
void	print_plane(t_plane *pl);


// utils_set.c
bool	set_double(double *target, char *input, double min, double max);
bool	set_tcolor(t_color *color, char **arr);
// bool	set_tpoint(t_vector *point, char **arr);
bool	set_tpoint(t_vector *point, char **arr);

bool	set_tnormvector(t_vector *vec, char **arr);
bool	set_int(int *target, char *input, int min, int max);

// utils_str.c
int		count_occurences(char *str, char c);
double	ft_strtod(char *input);

// errors.c
void	exit_onlymsg(char *msg);
void	exit_free(t_data *d, char *msg);

// shutdown.c
void	shutdown(t_data *d);

//plane
void	parse_plane(t_data *d, char **elements);
void	set_plane_anchor(t_data *d, t_plane *plane, char **elements);
void	set_plane_vector(t_data *d, t_plane *plane, char **elements);
void	set_plane_color(t_data *d, t_plane *plane, char **elements);

// // kris
// void	ite_ray(t_data *data);


#endif
