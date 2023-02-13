# include "../incl/minirt.h"

void	parsing(t_data *d, int fd)
{
	char	*line;

	line = gnl_trimmed(fd);
	while (line)
	{
		if (ft_strchr("#\n\0", (int)line[0]))
			free(line);
		else
			parse_line(d, line);
		line = gnl_trimmed(fd);
	}
	if (!d->amb_light.declared || !d->camera.declared)
		error_exit(d, E_MANDATORY);




	print_ambientlight(d);
	print_light(d);
	print_camera(d);
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
	if (!ft_strncmp(d->parse.elmnts[0], "A", 2))
		parse_ambientlight(d);
	else if (!ft_strncmp(d->parse.elmnts[0], "C", 2))
		parse_camera(d);
	else if (!ft_strncmp(d->parse.elmnts[0], "L", 2))
		parse_light(d);
	else if (!ft_strncmp(d->parse.elmnts[0], "sp", 3))
		parse_sphere(d);
	else if (!ft_strncmp(d->parse.elmnts[0], "pl", 3))
		parse_plane(d);
	else if (!ft_strncmp(d->parse.elmnts[0], "cy", 3))
		parse_cylinder(d);
	else
		error_exit(d, E_INVALOBJID);
	free_2d_char(d->parse.elmnts);
	d->parse.elmnts = NULL;
}
