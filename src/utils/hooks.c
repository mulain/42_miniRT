/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:44:08 by wmardin           #+#    #+#             */
/*   Updated: 2023/03/25 17:44:10 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_release(int key, t_data *d)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(d->mlx.mlx, d->mlx.win);
		free_all(d);
		exit(0);
	}
	return (1);
}

int	event_windowdestroy(t_data *d)
{
	free_all(d);
	exit(0);
}
