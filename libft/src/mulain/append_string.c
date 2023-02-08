/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:35:28 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/20 21:19:59 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Appends a string to a string array.
If the string array doesn't exist yet,
makes a new string array with the string as only content.
Frees the passed string array.
Danger! The intended use case is narrow. You might end up freeing stuff
you intended to keep.
It should mostly only be used for one and the same array.
Ok:				array_a = append_string(array_a, string);
Probably bad:	array_b = append_string(array_a, string);
It won't leak, but array_a is lost.
*/
char	**append_string(char **array, char *string)
{
	char	**result;
	int		i;

	if (!array)
	{
		result = malloc(2 * sizeof(char *));
		result[0] = string;
		result[1] = NULL;
		return (result);
	}
	i = 0;
	while (array[i])
		i++;
	result = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (array[i])
	{
		result[i] = array[i];
		i++;
	}
	result[i] = string;
	i++;
	result[i] = NULL;
	free(array);
	return (result);
}
