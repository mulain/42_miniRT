/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkformat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:37:30 by wmardin           #+#    #+#             */
/*   Updated: 2023/02/17 16:51:09 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
Conversions:
cspdiuxX%
• %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.
*/
int	ft_checkformat(const char c, va_list args)
{
	int		prints;

	prints = 0;
	if (c == 'c')
		prints = ft_printchar(va_arg(args, int));
	else if (c == 's')
		prints = ft_printstring(va_arg(args, char *));
	else if (c == 'p')
		prints = ft_printpointer(va_arg(args, unsigned long long));
	else if (c == 'd')
		prints = ft_printdecimal(va_arg(args, int));
	else if (c == 'i')
		prints = ft_printint(va_arg(args, int));
	else if (c == 'u')
		prints = ft_printunsignedint(va_arg(args, unsigned int));
	else if (c == 'x')
		prints = ft_printhex_lower(va_arg(args, int));
	else if (c == 'X')
		prints = ft_printhex_upper(va_arg(args, int));
	else if (c == '%')
		prints = ft_printchar('%');
	else if (c == 'f')
		prints = ft_printfloat(va_arg(args, double));
	return (prints);
}
