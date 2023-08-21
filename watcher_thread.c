/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   watcher_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 13:08:47 by rares         #+#    #+#                 */
/*   Updated: 2023/08/21 21:37:33 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*watcher_thread(void *data_pt)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *) data_pt;
	while (1)
	{
		pthread_mutex_lock(&data->check_rounds);
		if (data->completed_rounds == data->nr_philo)
		{
			pthread_mutex_unlock(&data->check_rounds);
			break ;
		}
		pthread_mutex_unlock(&data->check_rounds);
		if (is_dead(&data->philos[i]) == true)
		{
			pthread_mutex_lock(&data->check_status);
			data->philos[i].is_alive = false;
			pthread_mutex_unlock(&data->check_status);
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
		pthread_mutex_lock(&data->check_status);
		data->philos[i].is_alive = false;
		pthread_mutex_unlock(&data->check_status);
		i++;
	}
	return (NULL);
}

void	update_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->update_time);
	philo->time_last_meal = current_time();
	pthread_mutex_unlock(&philo->data->update_time);
}
