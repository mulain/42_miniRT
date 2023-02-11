# include "../incl/minirt.h"

int	count_occurences(char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

/* bool	check_and_strtod(char *input, double *value)
{
	if (!is_numbercharstr(input))
		return (true);
	
}




double	my_strtod(char *input)
{

}
 */
