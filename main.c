/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:16:19 by raanghel      #+#    #+#                 */
/*   Updated: 2023/09/04 14:15:14 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initializer(t_data *data, int argc, char **argv)
{
	if (initialize_data(data, argc, argv) == 1)
	{
		raise_error(data, "Failed to initialize data struct");
		return (1);
	}
	if (initialize_forks(data) == 1)
	{
		raise_error(data, "Failed to initialize mutexes");
		return (1);
	}
	if (initialize_philo_data(data) == 1)
	{
		raise_error(data, "Failed to initialize philo");
		return (1);
	}
	if (create_philos(data) == 1)
	{
		raise_error(data, "Failed to create philos");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
	{
		printf("Program should only have 4 or 5 arguments.");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		raise_error(data, "Failed to allocate memory for data struct");
		return (1);
	}
	if (initializer(data, argc, argv) == 1)
		return (1);
	if (free_data(data) == 1)
	{
		printf("Failed to free memory\n");
		return (1);
	}
	return (EXIT_SUCCESS);
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

// void	check(void)
// {
// 	system("leaks -q philo");
// }
// 	atexit(check);
