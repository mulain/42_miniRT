/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_precedingnode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:50:29 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/21 13:50:40 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Returns NULL if
- Passed node is first node
- Passed node is not present
The calling function should handle these cases separately.
*/
t_list	*get_precedingnode(t_list *node, t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp->next && temp->next != node)
		temp = temp->next;
	return (temp);
}
