# include "../incl/minirt.h"

/*
parse_line has to free line, because its subfunctions will abort the program
if an error is detected. If line were freed in the while loop here, it would
leak if a parsing error occurs.
*/
void	parsing(t_data *d, int argc, char **argv)
{
	int		fd;
	int		len;
	char	*line;

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
	char	*temp;

	temp = line;
	line = ft_strtrim(line, " \t\n\f\r\v");
	free(temp);
	if (line[0] == 'A')
		parse_ambientlight(d, line);
	/* else if (line[0] == 'C')

	else if (line[0] == 'L')

	else if (line[0] == 's' && line[1] == 'p')

	else if (line[0] == 'c' && line[1] == 'y')

	else if (line[0] == 'p' && line[1] == 'l')
 */
	else if (!line[0] || line[0] == '#')
	{
		free(line);
		return ;
	}
	else
	{
		free(line);
		exit_onlymsg(E_INVALOBJID);
	}
}
