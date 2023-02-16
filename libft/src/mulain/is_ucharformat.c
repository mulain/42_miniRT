/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ucharformat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:36:06 by wmardin           #+#    #+#             */
/*   Updated: 2023/02/16 21:36:10 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_ucharformat(char *input)
{
	int		val;

	val = ft_atoi(input);
	if (!is_onlydigits(input) || val < 0 || val > 255)
		return (false);
	return (true);
}
