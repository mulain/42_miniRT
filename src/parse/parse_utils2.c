/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:46:30 by wmardin           #+#    #+#             */
/*   Updated: 2023/03/25 17:48:42 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minirt.h"

t_phong	parse_phong(t_data *d, char *input, char *msg)
{
	t_3d		temp;

	temp = parse_point(d, input, msg);
	if (temp.x < 0 || temp.x > 1.0
		|| temp.y < 0 || temp.y > 1.0
		|| temp.z < 0 || temp.z > 1.0)
		error_exit(d, msg);
	return ((t_phong){temp.x, temp.y, temp.z});
}

void	set_range(t_data *d, double min, double max)
{
	d->parse.check_range = true;
	d->parse.min = min;
	d->parse.max = max;
}
