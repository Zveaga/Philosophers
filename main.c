/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:16:19 by raanghel      #+#    #+#                 */
/*   Updated: 2023/06/07 15:26:05 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

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

	printf("Nr philo: %d\n", data->nr_philo);
	printf("Die time: %d\n", data->nr_philo);
	printf("Eat_time: %d\n", data->nr_philo);
	printf("Sleep_time: %d\n", data->nr_philo);
	return (0);
}