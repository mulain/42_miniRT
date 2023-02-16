/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 07:51:38 by wmardin           #+#    #+#             */
/*   Updated: 2023/02/13 23:30:29 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *formatstr, ...);
int		ft_checkformat(const char c, va_list args);
int		ft_printchar(int c);
int		ft_printstring(char *str);
int		ft_printpointer(unsigned long long c);
int		ft_printdecimal(int c);
int		ft_printfloat(float f);
int		ft_printint(int c);
int		ft_printunsignedint(unsigned int c);
int		ft_printhex_lower(unsigned int c);
int		ft_printhex_upper(unsigned int c);

#endif
