# include "../incl/minirt.h"

bool	is_whitespace(char c)
{
	return (ft_strchr(" \t\n\f\r\v", c));
}

bool	is_decimalformat(char *input)
{
	int		i;
	bool	dot_found;

	dot_found = false;
	i = 1;
	if (input[0] < '0' || input[0] > '9')
	{
		if (input[0] != '-' && input[0] != '+' && input[0] != '.')
			return (0);
		if (!input[1])
			return (0);
		if (input[0] == '.')
			dot_found = true;
	}
	while (input[i])
	{
		if (input[i] < '0' || input[i] > '9')
			if (input [i] != '.' || dot_found)
				return (0);
		i++;
	}
	return (1);
}

bool	is_uchartriplet(char **array)
{
	int		i;
	int		val;

	i = 0;
	while (i < 3)
	{
		val = ft_atoi(array[i]);
		if (!ft_isdigit(array[i]) || val < 0 || val > 255)
			return (false)
		i++;
	}
}
