# include "../incl/minirt.h"

bool	is_whitespace(char c)
{
	return (ft_strchr(" \t\n\f\r\v", c));
}

bool	is_onlydigits(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_decimalformat(char *input)
{
	int		i;
	bool	dot_found;

	dot_found = false;
	i = 1;
	if (!ft_isdigit(input[0]))
	{
		if (!ft_strchr("-+.", (int)input[0]) || !input[1])
			return (false);
		if (input[0] == '.')
			dot_found = true;
		if (ft_strchr("-+", (int)input[0]) && input[1] == '.' && !input[2])
			return (false);
	}
	while (input[i])
	{
		if (!ft_isdigit(input[i]) && input[i] != '.')
			return (false);
		if (input[i] == '.' && dot_found)
			return (false);
		else
			dot_found = true;
		i++;
	}
	return (true);
}

bool	is_uchartriplet(char **array)
{
	int		i;
	int		val;

	i = 0;
	while (i < 3)
	{
		val = ft_atoi(array[i]);
		if (!is_onlydigits(array[i])
			|| val < 0 || val > 255)
			return (false);
		i++;
	}
	return (true);
}
