
#include "../incl/minirt.h"

bool	is_ucharformat(char *input)
{
	int		val;

	val = ft_atoi(input);
	if (!is_onlydigits(input) || val < 0 || val > 255)
		return (false);
	return (true);
}
