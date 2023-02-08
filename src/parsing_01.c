# include "../incl/minirt.h"

void	parsing(t_data *d, int argc, char **argv)
{
	int		fd;

	if (argc < 2)
		exit_msg(E_ARGCOUNT);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 4))
		exit_msg(E_FILETYPE);
	fd = open(argv[1], 0);
	if (fd == -1)
		exit_msg(E_OPENFILE);
	d->scene_name = argv[1];
}
