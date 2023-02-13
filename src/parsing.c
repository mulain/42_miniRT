# include "../incl/minirt.h"

void	parsing(t_data *d, int fd)
{
	char	*line;

	line = gnl_trimmed(fd);
	while (line)
	{
		parse_line(d, line);
		line = gnl_trimmed(fd);
	}
	print_objlist(d->objectlist);
}

char	*gnl_trimmed(int fd)
{
	char	*line;
	char	*temp;

	temp = get_next_line(fd);
	line = ft_strtrim(temp, " \t\n\f\r\v");
	free(temp);
	return (line);
}

void	parse_line(t_data *d, char *line)
{
	d->parse.elmnts = ft_split(line, ' ');
	free(line);
	if (skip_line(d))
		return ;
	if (!ft_strncmp(d->parse.elmnts[0], "A", 2))
		parse_ambientlight(d);
	else if (!ft_strncmp(d->parse.elmnts[0], "C", 2))
		parse_camera(d);
	else if (!ft_strncmp(d->parse.elmnts[0], "L", 2))
		parse_light(d);
	else if (!ft_strncmp(d->parse.elmnts[0], "sp", 3))
		parse_sphere(d);
/*
	else if (line[0] == 'c' && line[1] == 'y')

	else if (line[0] == 'p' && line[1] == 'l')
 */
	else
		error_exit(d, E_INVALOBJID);
	free_2d_char(d->parse.elmnts);
	d->parse.elmnts = NULL;
}

bool	skip_line(t_data *d)
{
	char	**elements;

	elements = d->parse.elmnts;
	if (!elements || !elements[0] || ft_strchr("#\n\0", (int)elements[0][0]))
	{
		free_2d_char(d->parse.elmnts);
		d->parse.elmnts = NULL;
		return (true);
	}
	return (false);
}
