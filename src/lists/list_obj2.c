/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_obj2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:46:42 by wmardin           #+#    #+#             */
/*   Updated: 2023/07/30 21:10:18 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minirt.h"

void	select_functions(t_objlst *new)
{
	select_intersect(new);
	select_normal(new);
}

/* 
Should use case instead of if here, but norm.
*/
void	select_intersect_safe(t_objlst *new)
{
	if (new->objtype == pl)
		new->get_intersection = intersect_plane;
	else if (new->objtype == di)
		new->get_intersection = intersect_disc;
	else if (new->objtype == tr)
		new->get_intersection = intersect_triangle;
	else if (new->objtype == sp)
		new->get_intersection = intersect_sphere;
	else if (new->objtype == tu)
		new->get_intersection = intersect_tube;
	else if (new->objtype == co)
		new->get_intersection = intersect_cone;
}

void	select_normal(t_objlst *new)
{
	if (new->objtype == pl)
		new->get_normal = normal_plane;
	else if (new->objtype == di)
		new->get_normal = normal_disc;
	else if (new->objtype == tr)
		new->get_normal = normal_triangle;
	else if (new->objtype == sp)
		new->get_normal = normal_sphere;
	else if (new->objtype == tu)
		new->get_normal = normal_tube;
	else if (new->objtype == co)
		new->get_normal = normal_cone;
}
