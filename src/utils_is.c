# include "../incl/minirt.h"

bool	is_whitespace(char c)
{
	return (ft_strchr(" \t\n\f\r\v", c));
}

bool	is_onlydigits(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (!ft_isdigit(input[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_decimalformat(char *input)
{
	int		i;

	if (count_occurences(input, '.') > 1)
		return (false);
	if (!ft_isdigit(input[0]))
	{
		if (!ft_strchr("-+.", (int)input[0]) || !input[1])
			return (false);
		if (input[1] == '.' && !input[2])
			return (false);
	}
	i = 1;
	while (input[i])
	{
		if (!ft_isdigit(input[i]) && input[i] != '.')
			return (false);
		i++;
	}
	return (true);
}

bool	is_ucharformat(char *input)
{
	int		val;

	val = ft_atoi(input);
	if (!is_onlydigits(input) || val < 0 || val > 255)
		return (false);
	return (true);
}
