# include "../incl/minirt.h"

void	parsing(t_data *d, int argc, char **argv)
{
	int		fd;
	int		len;
	char	*line;

	//(void)d;
	if (argc < 2)
		exit_onlymsg(E_ARGCOUNT);
	len = ft_strlen(argv[1]);
	if (len < 4)
		exit_onlymsg(E_FILENAME);
	if (ft_strncmp(argv[1] + len - 3, ".rt", 4))
		exit_onlymsg(E_FILETYPE);
	fd = open(argv[1], 0);
	if (fd == -1)
		exit_onlymsg(E_OPENFILE);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(d, line);
		line = get_next_line(fd);
	}
}

void	parse_line(t_data *d, char *line)
{
	char	**elements;

	elements = ft_split(line, ' ');
	free(line);
	if (!ft_strncmp(elements[0], "A", 2))
		parse_ambientlight(d, elements);
	else if (!ft_strncmp(elements[0], "C", 2))
		parse_camera(d, elements);



/*
	else if (line[0] == 'L')

	else if (line[0] == 's' && line[1] == 'p')

	else if (line[0] == 'c' && line[1] == 'y')

	else if (line[0] == 'p' && line[1] == 'l')
 */
	else if (!elements[0][0] || elements[0][0] == '#' || elements[0][0] == '\n')
	{
		free_2d_char(elements);
		return ;
	}
	else
	{
		free_2d_char(elements);
		exit_free(d, E_INVALOBJID);
	}
}
