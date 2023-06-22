/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:16:19 by raanghel      #+#    #+#                 */
/*   Updated: 2023/06/22 20:02:03 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void print_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		printf("Philo %d: lf %d and rf %d\n", i + 1 , data->philos[i].left_fork + 1, data->philos[i].right_fork + 1);
		i++;
	}
}

int	main( int argc, char **argv)
{
	t_data	*data;
	
	if (argc != 5)
	{
		raise_error("Program should have 4 arguments.");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		raise_error("Failed to allocate memory for data struct");

	if (initialize_data(data, argv) == 1)
	{
		raise_error("Failed to initialize data struct");
		return (1);
	}

	if (initialize_forks(data) == 1)
	{
		raise_error("Failed to initialize forks");
		return (1);
	}
	if (initialize_philo(data) == 1)
	{
		raise_error("Failed to initialize philo");
		return (1);
	}
	print_forks(data);
	// printf("Nr philo: %d\n", data->nr_philo);
	// printf("Die time: %d\n", data->nr_philo);
	// printf("Eat_time: %d\n", data->nr_philo);
	// printf("Sleep_time: %d\n", data->nr_philo);
	if (destroy_mutex(data) == 1)
	{
		printf("Failed to destroy mutex\n");		
		return (1);
	}

	
	return (0);
}

