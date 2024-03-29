/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:45:07 by wmardin           #+#    #+#             */
/*   Updated: 2023/03/25 17:45:09 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minirt.h"

int	main(int argc, char **argv)
{
	t_data		data;

	init_structs(&data);
	get_infile(&data, argc, argv);
	parse(&data);
	init_mlx(&data);
	if (USETHREADS)
		manage_threads(&data);
	else
		render(&data);
	mlx_put_image_to_window(data.mlx.mlx, data.mlx.win, data.mlx.img, 0, 0);
	mlx_key_hook(data.mlx.win, key_release, &data);
	mlx_hook(data.mlx.win, 17, 0L << 0, event_windowdestroy, &data);
	mlx_loop(data.mlx.mlx);
}

void	get_infile(t_data *d, int argc, char **argv)
{
	int		len;

	if (argc < 2)
		error_exit(d, E_ARGCOUNT);
	len = ft_strlen(argv[1]);
	if (len < 4)
		error_exit(d, E_FILENAME);
	if (ft_strncmp(argv[1] + len - 3, ".rt", 4))
		error_exit(d, E_FILETYPE);
	d->parse.fd = open(argv[1], 0);
	if (d->parse.fd == -1)
		error_exit(d, E_OPENFILE);
}

void	init_structs(t_data *d)
{
	d->width = IMG_WIDTH;
	d->height = IMG_HEIGHT;
	d->aspect_ratio = (double)d->width / (double)d->height;
	d->mlx.initialized = false;
	d->amb_light.brightness = 0.0;
	d->amb_light.color = (t_color){0, 0, 0, 0};
	d->amb_light.declared = false;
	d->camera.point = (t_3d){0, 0, 0};
	d->camera.vector = (t_3d){0, 0, 0};
	d->camera.x_axis = (t_3d){0, 0, 0};
	d->camera.y_axis = (t_3d){0, 0, 0};
	d->camera.fieldofview = 0;
	d->camera.fov_factor = 0.0;
	d->camera.declared = false;
	d->objectlist = NULL;
	d->lightlst = NULL;
	d->parse.fd = -1;
	d->parse.elmnts = NULL;
	d->parse.subelmnts = NULL;
	d->parse.check_range = false;
	d->parse.min = 0.0;
	d->parse.max = 0.0;
}

void	init_mlx(t_data *d)
{
	t_mlx		*m;

	m = &d->mlx;
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, d->width, d->height, "miniRT");
	m->img = mlx_new_image(m->mlx, d->width, d->height);
	m->img_addr = mlx_get_data_addr(m->img, &m->img_bpp, &m->img_line_length,
			&m->img_endian);
	m->img_bytespp = m->img_bpp / 8;
	m->initialized = true;
}

void	manage_threads(t_data *d)
{
	pthread_t		threads[THREADCOUNT];
	t_threadinfo	thr_info[THREADCOUNT];
	int				i;

	i = 0;
	while (i < THREADCOUNT)
	{
		thr_info[i].data = d;
		thr_info[i].id = i;
		if (pthread_create(&threads[i], NULL, render_threads, &thr_info[i]))
			error_exit(d, E_THREADCREATE);
		i++;
	}
	i = 0;
	while (i < THREADCOUNT)
	{
		if (pthread_join(threads[i], NULL))
			error_exit(d, E_THREADJOIN);
		i++;
	}
}
