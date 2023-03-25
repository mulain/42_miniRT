/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:43:59 by wmardin           #+#    #+#             */
/*   Updated: 2023/03/25 17:44:01 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_3d	add(t_3d p1, t_3d p2)
{
	return ((t_3d){p1.x + p2.x, p1.y + p2.y, p1.z + p2.z});
}

t_3d	subtract(t_3d p1, t_3d p2)
{
	return ((t_3d){p1.x - p2.x, p1.y - p2.y, p1.z - p2.z});
}

t_3d	scale(t_3d v, double mult)
{
	return ((t_3d){v.x * mult, v.y * mult, v.z * mult});
}

t_3d	reverse(t_3d v)
{
	return ((t_3d){-v.x, -v.y, -v.z});
}
