/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:32:38 by raanghel      #+#    #+#                 */
/*   Updated: 2023/09/07 18:00:06 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	current_time(void)
{
	struct timeval		tv;
	long int			current_time;	

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}

void	own_usleep(t_philo *philo, long milliseconds)
{
	long int		start_time;

	start_time = current_time();
	while ((current_time() - start_time) < milliseconds)
	{
		if (check_if_stop(philo->data) == true || check_if_full(philo) == true)
			break ;
		usleep(200);
	}
}

bool	is_dead(t_philo *philo)
{
	bool			status;

	pthread_mutex_lock(&philo->data->update_time);
	if (current_time() - philo->time_last_meal >= philo->data->die_time)
		status = true;
	else
		status = false;
	pthread_mutex_unlock(&philo->data->update_time);
	return (status);
}

bool	check_if_full(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&philo->data->check_rounds);
	if (philo->fully_ate == true)
		status = true;
	else
		status = false;
	pthread_mutex_unlock(&philo->data->check_rounds);
	return (status);
}
