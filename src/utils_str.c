# include "../incl/minirt.h"

int	count_occurences(char *str, char c)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

int	count_subelements(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	return (i + 1);
}

/*
Caveats:
- 	Relies on prior syntax checking (is_decimalformat)
-	Does not handle exponent notation
*/
double	ft_strtod(char *input)
{
	double		result;
	double		fraction;
	int			sign;
	int			n_fraction;

	result = 0;
	fraction = 0;
	n_fraction = 1;
	sign = 1;
	if (*input == '-')
	{
		sign = -1;
		input++;
	}
	else if (*input == '+')
		input++;
	while (ft_isdigit(*input))
	{
		result = result * 10 + *input - 48;
		input++;
	}
	if (*input == '.' )
	{
		input++;
		while (ft_isdigit(*input))
		{
			fraction = fraction * 10 + *input - 48;
			n_fraction *= 10;
			input++;
		}
	}
	result += fraction / n_fraction;
	result *= sign;
	return (result);
}
