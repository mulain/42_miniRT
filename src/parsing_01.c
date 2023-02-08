# include "../incl/minirt.h"

void	parsing(t_data *d, int argc, char **argv)
{
	if (argc < 2)
		exit_msg(E_ARGCOUNT);
	d->scene_name = argv[1];
}
