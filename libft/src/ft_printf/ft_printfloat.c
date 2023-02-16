/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfloat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:08:19 by wmardin           #+#    #+#             */
/*   Updated: 2023/02/15 20:05:06 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define PRECISION	100

double	mu_floor(double x)
{
	return ((int)x - (x < 0 && x != (int)x));
}

double	mu_fmod(double x, double y)
{
	return (x - y * mu_floor(x / y));
}

/*
quickndirty, just wanna print real quick.
but started structure to make a real print float later maybe
(not just casting to int right away even though right now its actually worse)
*/
int	ft_printfloat(float f)
{
	int		prints;
	double	fraction;

	prints = 1;
	if (f < 0)
	{
		prints += write(1, "-", 1);
		f = -f;
	}
	fraction = mu_fmod(f, 1.0);
	f = mu_floor(f);
	prints += ft_printint(f);
	fraction *= PRECISION;
	prints += write(1, ".", 1);
	prints += ft_printint((int)fraction);
	return (prints);
}

/* int main()
{
	double	mod;

	mod = mu_fmod(10.1, 1.0);
	printf("fracmodulo:%f\n", mod);
	ft_printfloat(1567.12323232);
	write (1, "\n", 1);
} */