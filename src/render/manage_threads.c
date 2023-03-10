
#include "../incl/minirt.h"

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
		if (pthread_create(&threads[i], NULL, render, &thr_info[i]))
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
