
#ifndef STRUCTS_H
# define STRUCTS_H

#include "defines.h"

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

// Helper for functions that need more variables than 42 norm allows
typedef struct s_helper
{
	double		a;
	double		b;
	double		c;
	double		d1;
	double		d2;
	double		d3;
	double		m;
	t_3d		oc;
}	t_helper;

typedef struct s_inthelper
{
	int			id;
	int			x;
	int			y;
	int			job;
}	t_inthelp;

typedef struct s_trihelper
{
	t_3d		side_a;
	t_3d		side_b;
	t_3d		side_c;
	t_3d		p1_to_p;
	t_3d		p2_to_p;
	t_3d		p3_to_p;
}	t_trihelp;

typedef struct s_rgb_intensity
{
	double		r;
	double		g;
	double		b;
}	t_rgb;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			trgb;
}	t_color;

// forward declaration
typedef struct s_objlst		t_objlst;

typedef struct s_intersection
{
	t_objlst	*objnode;
	double		distance;
	t_3d		point;
	t_color		color;
}	t_intrsct;

typedef struct s_light
{
	t_3d		origin;
	double		brightness;
	t_color		color;
	bool		declared;
}	t_light;

typedef struct s_camera
{
	t_3d		point;
	t_3d		vector;
	t_3d		x_axis;
	t_3d		y_axis;
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
	t_3d		v1;
	t_3d		v2;
	t_3d		v3;
	t_3d		vector;
	t_color		color;
}	t_triangle;

typedef struct s_sphere
{
	t_3d		center;
	t_color		color;
	double		radius;
}	t_sphere;

typedef struct s_tube
{
	t_3d		base;
	t_3d		top;
	t_3d		axis;
	double		radius;
	double		height;
	t_color		color;
}	t_tube;

typedef struct s_cone
{
	t_3d		base;
	t_3d		apex;
	t_3d		axis;
	double		radius;
	double		height;
	double		theta_rad;
	double		theta_deg;
	t_color		color;
}	t_cone;

// Struct for parse
typedef struct s_parse
{
	int			fd;
	char		**elmnts;
	char		**subelmnts;
	double		min;
	double		max;
}	t_parse;

// forward declaration
typedef struct s_objlst		t_objlst;
typedef struct s_lightlst	t_lightlst;

typedef struct s_data
{
	t_mlx			mlx;
	t_ambientlight	amb_light;
	t_camera		camera;
	t_lightlst		*lightlst;
	t_objlst		*objectlist;
	t_parse		parse;
	int				width;
	int				height;
	float			aspect_ratio;
	float			fov_ratio;
}	t_data;

// struct for threads
typedef struct s_threadinfo
{
	t_data	*data;
	int		id;
}	t_threadinfo;

#endif
