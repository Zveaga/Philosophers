/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:51:21 by raanghel      #+#    #+#                 */
/*   Updated: 2023/08/23 20:42:04 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	initialize_data(t_data *data, int argc, char **argv)
{
	if (check_data(argc, argv) == 1)
	{
		printf("Invalid arguments.\n");
		return (1);
	}
	data->philo_alive = true;
	data->nr_philo = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->philos = NULL;
	data->forks = NULL;
	data->completed_rounds = 0;
	if (argc == 6)
		data->required_rounds = ft_atoi(argv[5]);
	else
		data->required_rounds = -1;
	return (0);
}

int	initialize_forks(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->check_rounds, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->printing, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->update_time, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->check_status, NULL) != 0)
		return (1);
	data->forks = malloc(data->nr_philo * sizeof(pthread_mutex_t));
	if (data->forks == NULL)
		return (1);
	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	initialize_philo_data(t_data *data)
{
	int			i;

	data->philos = malloc(data->nr_philo * sizeof(t_philo));
	if (data->philos == NULL)
		return (1);
	i = 0;
	while (i < data->nr_philo)
	{
		data->philos[i].is_eating = false;
		data->philos[i].fully_ate = false;
		data->philos[i].is_alive = true;
		data->philos[i].eat_rounds = 0;
		data->philos[i].pos = i + 1;
		data->philos[i].ms = 0;
		data->philos[i].time_last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = i;
		if (i == 0)
			data->philos[i].right_fork = data->nr_philo - 1;
		else
			data->philos[i].right_fork = i - 1;
		i++;
	}
	return (0);
}

static int	destroy_simple_mutex(t_data *data)
{
	if (pthread_mutex_destroy(&data->check_rounds) != 0)
		return (1);
	if (pthread_mutex_destroy(&data->update_time) != 0)
		return (1);
	if (pthread_mutex_destroy(&data->printing) != 0)
		return (1);
	if (pthread_mutex_destroy(&data->check_status) != 0)
		return (1);
	return (0);
}

int	free_data(t_data *data)
{
	int	i;

	if (data == NULL)
		return (0);
	if (data->forks != NULL)
	{
		if (destroy_simple_mutex(data) != 0)
			return (1);
	}
	if (data->philos != NULL)
	{
		i = 0;
		while (i < data->nr_philo)
		{
			if (pthread_mutex_destroy(&data->forks[i]) != 0)
				return (1);
			i++;
		}
		free(data->forks);
		free(data->philos);
	}
	if (data->philos == NULL && data->forks != NULL)
		free(data->forks);
	free(data);
	return (0);
}
