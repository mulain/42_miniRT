# include "../incl/minirt.h"

int	main (int argc, char **argv)
{
	//t_data		*data;

	if (argc < 2)
		exit_msg(E_ARGCOUNT);
	ft_printf("%s\n", argv[1]);

}
