/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_singlechar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:35:28 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/20 21:20:10 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Deletes the char at the position "del_pos" of the string "string".
*/
char	*del_singlechar(char *string, int del_pos)
{
	char	*result;

	if (!string)
		return (NULL);
	string[del_pos] = 0;
	result = ft_strjoin(string, string + del_pos + 1);
	free(string);
	return (result);
}
