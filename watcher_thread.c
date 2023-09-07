/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   watcher_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 13:08:47 by rares         #+#    #+#                 */
/*   Updated: 2023/09/07 15:40:21 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->check_status);
	data->stop = true;
	pthread_mutex_unlock(&data->check_status);
}

bool	check_if_stop(t_data *data)
{
	bool	status;

	pthread_mutex_lock(&data->check_status);
	status = data->stop;
	pthread_mutex_unlock(&data->check_status);
	return (status);
}

void	*watcher_thread(void *data_pt)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *) data_pt;
	while ((check_if_stop(data) == false))
	{
		if (is_dead(&data->philos[i]) == true)
		{
			//own_usleep(&data->philos[i], 10);
			output_message(&data->philos[i], DEAD);
			stop_simulation(data);
			break ;
		}
		if (i == data->nr_philo)
			i = 0;
	}
	stop_simulation(data);
	return (NULL);
}

// static void	set_death(t_data *data, int i)
// {
// 	pthread_mutex_lock(&data->check_status);
// 	data->philos[i].is_alive = false;
// 	pthread_mutex_unlock(&data->check_status);
// }
// printf(YELLOW"\n(%ld) Philo %d died!\n"RESET,
// 	current_time() - data->start_time, data->philos[i].pos);

// bool	check_if_alive(t_philo *philo)
// {
// 	bool	status;

// 	pthread_mutex_lock(&philo->data->check_status);
// 	status = philo->is_alive;
// 	pthread_mutex_unlock(&philo->data->check_status);
// 	return (status);
// }
