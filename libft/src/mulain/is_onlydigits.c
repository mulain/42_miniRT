/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_onlydigits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:56:39 by wmardin           #+#    #+#             */
/*   Updated: 2023/02/13 20:04:16 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
