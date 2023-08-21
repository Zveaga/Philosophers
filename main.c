/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:16:19 by raanghel      #+#    #+#                 */
/*   Updated: 2023/08/21 21:30:01 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	check(void)
{
	system("leaks philo");
}

void	print_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		printf("Philo %d: lf %d and rf %d\n", i + 1 , data->philos[i].left_fork + 1, data->philos[i].right_fork + 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;
	atexit(check);
	if (argc != 5 && argc != 6)
	{
		raise_error("Program should only have 4 or 5 arguments.");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		raise_error("Failed to allocate memory for data struct");
	if (initialize_data(data, argc, argv) == 1)
	{
		raise_error("Failed to initialize data struct");
		return (1);
	}
	if (initialize_forks(data) == 1)
	{
		raise_error("Failed to initialize forks");
		return (1);
	}
	if (initialize_philo_data(data) == 1)
	{
		raise_error("Failed to initialize philo");
		return (1);
	}
	if (create_philos(data) == 1)
	{
		raise_error("Failed to create philos");
		return (1);
	}
	if (free_data(data) == 1)
	{
		printf("Failed to free memory\n");
		return (1);
	}
	return (EXIT_SUCCESS);
}

// if (data->completed_rounds == data->nr_philo)
	// 	printf("\n----ALL PHILOSOPHERS ATE ENOUGH FOOD----\n");
	//print_forks(data);
	// printf("Nr philo: %d\n", data->nr_philo);
	// printf("Die time: %d\n", data->nr_philo);
	// printf("Eat_time: %d\n", data->nr_philo);
	// printf("Sleep_time: %d\n", data->nr_philo);
	//sleep(1);