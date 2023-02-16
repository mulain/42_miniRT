/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_strtod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:24:03 by wmardin           #+#    #+#             */
/*   Updated: 2023/02/15 19:41:43 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	get_fraction(char *input)
{
	double		fraction;
	int			n_fraction;

	fraction = 0;
	n_fraction = 1;
	while (ft_isdigit(*input))
	{
		fraction = fraction * 10 + *input - 48;
		n_fraction *= 10;
		input++;
	}
	return (fraction / n_fraction);
}

/*
Caveats:
- 	Relies on prior syntax checking (is_decimalformat)
-	Does not handle overflow
-	Does not handle exponent notation
*/
double	conv_strtod(char *input)
{
	double		result;
	int			sign;

	result = 0;
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
		result += get_fraction(input + 1);
	return (result * sign);
}
