
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

# define E_ARGCOUNT		"Wrong number of arguments. Please supply scene file.\n"
# define E_FILETYPE		"Wrong input file type. Please supply a .rt file.\n"
# define E_FILENAME		"Invalid input file name.\n"
# define E_INVALOBJID	"Invalid object identifier encountered.\n"
# define E_AMBLIGHTDEF	"Ambient light (A): may only be defined once.\n"
# define E_AMBLIGHT1	"Ambient light (A): invalid first argument.\n"
# define E_CAMERA		"Camera (C): may only be defined once.\n"
# define E_LIGHT		"Light (L) may only be defined once.\n"
# define E_OPENFILE		"Could not open input file.\n"

// main.c

void	init_structs(t_data *d);
void	init_mlx(t_data *d);

// parsing_01.c
void	parsing(t_data *d, int argc, char **argv);
void	parse_line(t_data *d, char *line);

// parsing_objects.c
void	parse_ambientlight(t_data *d, char **elements);

// utils_is.c
bool	is_whitespace(char c);
bool	is_onlydigits(char *str);
bool	is_decimalformat(char *input);
bool	is_uchartriplet(char **array);

// utils_calc.c
double	my_strtod(char *input);

// errors.c
void	exit_onlymsg(char *msg);
void	exit_free(t_data *d, char *msg);

// shutdown.c
void	shutdown(t_data *d);

#endif
