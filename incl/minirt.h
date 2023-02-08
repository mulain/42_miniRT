
#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

# include "../libft/include/libft.h"

# define E_ARGCOUNT		"Wrong number of arguments. Please supply scene file.\n"

typedef struct s_data
{
	char			*scene_name;
}	t_data;


// parsing_01.c
void	parsing(t_data *d, int argc, char **argv);


// errors.c
void	exit_msg(char *msg);

#endif
