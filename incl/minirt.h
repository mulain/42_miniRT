
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
# include "defines.h"

// main.c
void	init_structs(t_data *d);
void	init_mlx(t_data *d);

// parsing.c
void	parsing(t_data *d, int argc, char **argv);
void	parse_line(t_data *d, char *line);

// parsing_ambientlight.c
void	parse_ambientlight(t_data *d, char **elements);
void	check_declared_amblight(t_data *d, char **elements);
void	set_amblight_lightingratio(t_data *d, char **elements);
void	set_amblight_color(t_data *d, char **elements);

// parsing_camera.c
void	parse_camera(t_data *d, char **elements);
void	check_declared_camera(t_data *d, char **elements);
void	set_camera_viewpoint(t_data *d, char **elements);
void	set_camera_normvector(t_data *d, char **elements);



// utils_is.c
bool	is_whitespace(char c);
bool	is_onlydigits(char *str);
bool	is_decimalformat(char *input);
bool	is_ucharformat(char *input);

// utils_str.c
int		count_occurences(char *str, char c);
double	ft_strtod(char *input);

// utils_set.c
bool	set_double(double *target, char *input);
bool	set_tcolor(t_color *color, char **arr);
bool	set_tpoint(t_point *point, char **arr);
bool	set_tnormvector(t_normvector *vec, char **arr);

// errors.c
void	exit_onlymsg(char *msg);
void	exit_free(t_data *d, char *msg);

// shutdown.c
void	shutdown(t_data *d);

#endif
