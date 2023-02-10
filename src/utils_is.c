# include "../incl/minirt.h"

bool	is_whitespace(char c)
{
	return (ft_strchr(" \t\n\f\r\v", c));
}

bool	is_numberchar(char c)
{
	return (ft_strchr("0123456789.,-+", c));
}

bool	is_numbercharstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!is_numberchar(str[i]))
			return (false);
		i++;
	}
	return (true);
}
