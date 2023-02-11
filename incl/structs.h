
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
}	t_mlx;

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

typedef struct s_light
{
	t_point		coordinates;
	double		brightness; //0.0 to 1.0
	t_color		color;
	bool		declared;
}	t_light;

typedef struct s_camera
{
	t_point		viewpoint;
	t_point		orientation_vector; // range -1 to 1
	int			fieldofview; // 0 to 180
	bool		declared;
}	t_camera;

typedef struct s_ambientlight
{
	double		brightness; //0.0 to 1.0
	t_color		color;
	bool		declared;
}	t_ambientlight;

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
	 maybe name too long. i would request using 
	 long names because it is so easy to read. and it really distinguishes
	 that this is a vector not a point. Could also make a separate struct
	 t_normvector or smth (which would however have the exact same content, i.e.
	 3 doubles).
	 */ 
	t_point		orientation_vector; // range -1 to 1
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_point		anchor;
	t_point		orientation_vector; // range -1 to 1
	double		d;
	double		h;
	t_color		color;
}	t_cylinder;

typedef struct s_data
{
	t_mlx			mlx;
	t_ambientlight	amb_light;
	t_camera		camera;
	t_light			light;
	//Linked list for all the objects?
	char			*line;
	char			**elements_a;
	char			**elements_b;

}	t_data;

#endif
