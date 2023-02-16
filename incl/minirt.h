
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

// calc_vector.c
double	normvector_length(t_normvector vec);

// main.c
void	get_infile(t_data *d, int argc, char **argv);
void	init_structs(t_data *d);
void	init_mlx(t_data *d);

// parsing.c
void	parsing(t_data *d);
char	*gnl_trimmed(int fd);
void	parse_line(t_data *d, char *line);

// parsing_lightsandcam.c
void	parse_ambientlight(t_data *d);
void	parse_camera(t_data *d);
void	parse_light(t_data *d);

// parsing_objects.c
void	parse_sphere(t_data *d);
void	parse_plane(t_data *d);
void	parse_cylinder(t_data *d);

// parsing_utils.c
void	parse_double(t_data *d, double *target, int index, char *msg);
void	parse_tcolor(t_data *d, t_color *color, int index, char *msg);
void	parse_tpoint(t_data *d, t_point *point, int index, char *msg);
void	parse_tnormvector(t_data *d, t_normvector *vec, int index, char *msg);
void	parse_int(t_data *d, int *target, int index, char *msg);

// utils_is.c
bool	is_ucharformat(char *input);

// utils_print1.c
void	print_objlist(t_objlist *lst);
void	print_ambientlight(t_data *d);
void	print_camera(t_data *d);
void	print_light(t_data *d);

// utils_print2.c
void	print_sphere(t_sphere *sp);
void	print_plane(t_plane *pl);
void	print_cylinder(t_cylinder *cy);

// shutdown.c
void	error_exit(t_data *d, char *msg);
void	free_all(t_data *d);

#endif
