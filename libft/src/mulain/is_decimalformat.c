/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_decimalformat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:20:56 by wmardin           #+#    #+#             */
/*   Updated: 2023/02/15 18:21:12 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
