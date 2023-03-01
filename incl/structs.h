
#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_addr;
	int		img_bpp;
	int		img_bytespp;
	int		img_line_length;
	int		img_endian;
	bool	initialized;
}	t_mlx;

// Cartesian representation of a vector or point in 3D Euclidean space.
typedef struct s_3d
{
	double		x;
	double		y;
	double		z;
}	t_3d;

// Helper for parsing objects that need more variables than norm allows
typedef struct s_helper
{
	double		a;
	double		b;
	double		c;
	t_3d		oc;
}	t_helper;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			trgb;
}	t_color;

typedef struct s_intersection
{
	double		distance;
	t_3d		point;
	t_color		color;
}	t_intrsct;

typedef struct s_light
{
	t_3d		point;
	double		brightness;
	t_color		color;
	bool		declared;
}	t_light;

typedef struct s_camera
{
	t_3d		point;
	t_3d		vector;
	int			fieldofview;
	double		fov_factor;
	bool		declared;
}	t_camera;

typedef struct s_ambientlight
{
	double		brightness;
	t_color		color;
	bool		declared;
}	t_ambientlight;

// Objects

typedef struct s_ray
{
	t_3d	origin;
	t_3d	direction;
}	t_ray;

typedef struct s_plane
{
	t_3d		point;
	t_3d		vector;
	t_color		color;
}	t_plane;

typedef struct s_disc
{
	t_3d		center;
	t_3d		vector;
	double		radius;
	t_color		color;
}	t_disc;

typedef struct s_triangle
{
	t_3d		p1;
	t_3d		p2;
	t_3d		p3;
	t_color		color;
}	t_triangle;

typedef struct s_sphere
{
	t_3d		center;
	t_color		color;
	double		radius;
}	t_sphere;


typedef struct s_cylinder
{
	t_3d		base;
	t_3d		top;
	t_3d		axis;
	double		radius;
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

// The main struct
typedef struct s_data
{
	t_mlx			mlx;
	t_ambientlight	amb_light;
	t_camera		camera;
	t_light			light;
	t_objlist		*objectlist;
	t_parsing		parse;
	int				width;
	int				height;
	float			aspect_ratio;
	float			fov_ratio;
}	t_data;

#endif
