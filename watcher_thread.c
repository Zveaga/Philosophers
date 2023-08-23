/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   watcher_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 13:08:47 by rares         #+#    #+#                 */
/*   Updated: 2023/08/23 20:50:12 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

static void	set_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->check_status);
	data->philos[i].is_alive = false;
	pthread_mutex_unlock(&data->check_status);
}

void	*watcher_thread(void *data_pt)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *) data_pt;
	while (check_if_full(data) == false)
	{
		if (is_dead(&data->philos[i]) == true)
		{
			set_death(data, i);
			printf(YELLOW"\n(%ld) Philo %d died!\n"RESET,
				current_time() - data->start_time, data->philos[i].pos);
			break ;
		}
		if (i == data->nr_philo)
			i = 0;
	}
	i = 0;
	while (i < data->nr_philo)
	{
		set_death(data, i);
		i++;
	}
	return (NULL);
}
