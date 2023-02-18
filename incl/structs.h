
#ifndef STRUCTS_H
# define STRUCTS_H

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
	bool	initialized;
}	t_mlx;

typedef struct s_helper
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		intersect_1;
	double		intersect_2;
}	t_helper;

/*
Cartesian representation of a point in 3D Euclidean space.
*/
typedef struct s_point
{
	double		x;
	double		y;
	double		z;
}	t_point;

/*
Cartesian representation of a vector in 3D Euclidean space.
Not necessary to differentiate point from vector from a coding
point of view, but it's cleaner for math purposes.
*/
typedef struct s_vector
{
	double		x;
	double		y;
	double		z;
}	t_vector;

typedef struct s_ray
{
	t_point		point;
	t_vector	vector;
}	t_ray;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}	t_color;

typedef struct s_light
{
	t_point		point;
	double		brightness;
	t_color		color;
	bool		declared;
}	t_light;

typedef struct s_camera
{
	t_point		point;
	t_vector	vector;
	int			fieldofview;
	bool		declared;
}	t_camera;

typedef struct s_ambientlight
{
	double		brightness;
	t_color		color;
	bool		declared;
}	t_ambientlight;

typedef struct s_sphere
{
	t_point		point;
	t_color		color;
	double		radius;
}	t_sphere;

typedef struct s_plane
{
	t_point		point;
	t_vector	vector;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_point		point;
	t_vector	vector;
	double		diameter;
	double		height;
	t_color		color;
}	t_cylinder;

// Struct for parsing
typedef struct s_parsing
{
	int			fd;
	char		**elmnts;
	char		**subelmnts;
	double		min;
	double		max;
}	t_parsing;

// Forward declaration
typedef struct s_objlist	t_objlist;

/*
The main struct.
*/
typedef struct s_data
{
	t_mlx			mlx;
	t_ambientlight	amb_light;
	t_camera		camera;
	t_light			light;
	t_objlist		*objectlist;
	t_parsing		parse;
}	t_data;

#endif
