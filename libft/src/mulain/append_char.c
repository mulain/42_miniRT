/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:35:28 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/14 10:41:52 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Appends a char to a string. If the string doesn't exist yet,
makes a new string with the char as only content.
Has an extra test for !string and char == 0 to prevent the resulting
string from being 00. If !string and the char is 0, only callocs for the 0 byte,
so the resulting string is 0. This can happen when creating empty substrings,
i.e. "".
Frees the passed string.
Danger! The intended use case is narrow. You might end up freeing stuff
you intended to keep.
It should mostly only be used for one and the same string.
Ok:				string_a = appendchar(string_a, char c);
Probably bad:	string_b = appendchar(string_a, char c);
It won't leak, but string_a is lost.
*/
char	*append_char(char *string, char c)
{
	char	*result;
	int		i;

	if (!string && c == 0)
		return (ft_calloc(1, sizeof(char)));
	if (!string)
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = c;
		return (result);
	}
	result = ft_calloc(ft_strlen(string) + 2, sizeof(char));
	i = 0;
	while (string[i])
	{
		result[i] = string[i];
		i++;
	}
	result[i] = c;
	free (string);
	return (result);
}
