/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:46:36 by wmardin           #+#    #+#             */
/*   Updated: 2023/03/25 17:46:37 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minirt.h"

t_lightlst	*lightlst_new(t_data *d, t_light light)
{
	t_lightlst		*new;

	new = malloc(sizeof(t_lightlst));
	if (!new)
		error_exit(d, E_MALLOC);
	new->origin = light.origin;
	new->brightness = light.brightness;
	new->color = light.color;
	new->next = NULL;
	return (new);
}

void	lightlst_add_back(t_lightlst **lst, t_lightlst *new)
{
	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else
		(lightlst_last(*lst))->next = new;
}

t_lightlst	*lightlst_last(t_lightlst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lightlst_free(t_lightlst *lst)
{
	t_lightlst	*temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}
