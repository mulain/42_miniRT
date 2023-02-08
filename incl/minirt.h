
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
	
	char	*scene_name;
}	t_data;


// parsing_01.c
void	parsing(t_data *d, int argc, char **argv);

// setup_01.c
void	init_mlx(t_data *d);


// errors.c
void	exit_msg(char *msg);

#endif
