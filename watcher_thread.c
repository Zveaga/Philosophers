/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   watcher_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 13:08:47 by rares         #+#    #+#                 */
/*   Updated: 2023/09/26 11:58:46 by raanghel      ########   odam.nl         */
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

void	print_death_message(t_philo *philo)
{
	long int	curr_time;

	if (check_if_full(philo) == true)
		return ;
	curr_time = current_time() - philo->data->start_time;
	printf(YELLOW"(%ld) Philo %d died\n"RESET, curr_time, philo->pos);
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
			stop_simulation(data);
			print_death_message(&data->philos[i]);
			break ;
		}
		if (i == data->nr_philo)
			i = 0;
	}
	stop_simulation(data);
	return (NULL);
}
