
#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

# include "../mlx/mlx.h"
# include "../libft/include/libft.h"

# define E_ARGCOUNT		"Wrong number of arguments. Please supply scene file.\n"
# define E_FILETYPE		"Wrong input file type. Please supply a .rt file.\n"
# define E_OPENFILE		"Could not open input file.\n"

typedef struct s_data
{
	t_mlx	mlx;
	//Linked list for all the objects?


	char	*scene_name;
}	t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		win_width;
	int		win_height;
	void	*img;
	char	*img_addr;
	int		img_bpp;
	int		img_bytespp;
	int		img_line_length;
	int		img_endian;
	int		img_width;
	int		img_height;
}	t_mlx;

// Object structs - could move these to a separate h file if it gets too crowded
typedef struct s_sphere
{
	t_point		center;
	t_color		color;
	double		d;
}	t_sphere;

typedef struct s_plane
{
	t_point		anchor;
	 /*has same data as a point but is ackchually a vector: range -1 to 1
	 maybe name too long. if norm fucks us, change it. i would request using 
	 long names because it is so easy to read. and it really distinguishes
	 that this is a vector not a point. Could also make a separate struct
	 from t_point (which would however have the exact same content, i.e.
	 3 doubles).
	 */ 
	t_point		orientation_vector;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_point		anchor;
	double		d;
	double		h;
	t_color		color;
}	t_cylinder;


// General attribute structs for use across different objects

//unsure about range for these. prolly unlimited and
//we translate to our system later
typedef struct s_point
{
	double		x;
	double		y;
	double		z;
}	t_point;

//i just love ints, what can i say? range ofc 0-255
typedef struct s_color
{
	int			x;
	int			y;
	int			z;
}	t_color;

// parsing_01.c
void	parsing(t_data *d, int argc, char **argv);

// setup_01.c
void	init_mlx(t_data *d);

// errors.c
void	exit_msg(char *msg);

#endif
