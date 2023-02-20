/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_multichar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:25:14 by wmardin           #+#    #+#             */
/*   Updated: 2023/02/20 13:35:35 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
Works like ft_split, but takes a string as an argument and splits
whenever a char of that string is found.
*/
char	**split_multichar(char const *string, char *splitters)
{
	int		i;
	char	*s;
	char	*s_save;
	char	**out;

	if (!string)
		return (NULL);
	s = ft_strtrim(string, splitters);
	s_save = s;
	out = NULL;
	while (*s)
	{
		while (*s && ft_strchr(splitters, (int)*s))
			s++;
		i = 0;
		while (s[i] && !ft_strchr(splitters, (int)s[i]))
			i++;
		out = append_string(out, ft_substr(s, 0, i));
	s += i;
	}
	free(s_save);
	return (out);
}
