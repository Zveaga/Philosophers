/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 13:01:48 by rares         #+#    #+#                 */
/*   Updated: 2023/08/21 17:58:50 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

static int	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->right_fork]) != 0)
		return (1);
	output_message(philo, FORK_R);
	if (pthread_mutex_lock(&philo->data->forks[philo->left_fork]) != 0)
		return (1);
	output_message(philo, FORK_L);
	return (0);
}

int	return_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->data->forks[philo->left_fork]) != 0)
		return (1);
	output_message(philo, RLS_FORK_L);
	if (pthread_mutex_unlock(&philo->data->forks[philo->right_fork]) != 0)
		return (1);
	output_message(philo, RLS_FORK_R);
	return (0);
}

static void	eat(t_philo *philo)
{
	update_time_last_meal(philo);
	philo->eat_rounds++;
	if (philo->eat_rounds == philo->data->required_rounds)
	{
		pthread_mutex_lock(&philo->data->check_rounds);
		philo->data->completed_rounds++;
		pthread_mutex_unlock(&philo->data->check_rounds);
		//return_forks(philo);
		//philo->fully_ate = true;
	}
	output_message(philo, EAT);
	own_usleep(philo, philo->data->eat_time);
}

static void	*routine(void *philo_pt)
{
	t_philo		*philo;

	philo = (t_philo *)philo_pt;
	if (philo->pos % 2 == 0)
		own_usleep(philo, 10);
	while (philo->fully_ate == false)
	{
		pthread_mutex_lock(&philo->data->check_status);
		if (philo->is_alive == false)
		{
			pthread_mutex_unlock(&philo->data->check_status);
			break ;
		}
		pthread_mutex_unlock(&philo->data->check_status);
		if (take_forks(philo) == 1)
			return (NULL);
		eat(philo);
		if (return_forks(philo) == 1)
			return (NULL);
		output_message(philo, SLEEP);
		own_usleep(philo, philo->data->sleep_time);
		output_message(philo, THINK);
	}
	return (NULL);
}

int	create_philos(t_data *data)
{
	int			i;
	pthread_t	watcher;

	i = 0;
	data->start_time = current_time();
	while (i < data->nr_philo)
	{
		update_time_last_meal(&data->philos[i]);
		if (pthread_create(&data->philos[i].thread_id, NULL, &routine,
				&data->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&watcher, NULL, &watcher_thread, data) != 0)
		return (1);
	if (pthread_join(watcher, NULL) != 0)
		return (1);
	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
