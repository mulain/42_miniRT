# include "../incl/minirt.h"

void	exit_onlymsg(char *msg)
{
	write (2, msg, ft_strlen(msg));
	exit(1);
}

void	exit_free(t_data *d, char *msg)
{
	free_all(d);
	exit_onlymsg(msg);
}

void	free_all(t_data *d)
{
	if (d->parse.input)
		free(d->parse.input);
	if (d->parse.elmnts)
		free_2d_char(d->parse.elmnts);
	if (d->parse.subelmnts)
		free_2d_char(d->parse.subelmnts);
	if (d->objectlist)
		objlist_free(d->objectlist);
}
