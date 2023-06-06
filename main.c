/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:16:19 by raanghel      #+#    #+#                 */
/*   Updated: 2023/06/06 17:07:21 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	main( int argc, char **argv)
{
	t_data	*data;
	
	if (argc > 5)
		raise_error("Program should have 4 arguments.");
	data = malloc(sizeof(t_data));
	if (!data)
		raise_error("Failed to allocate memory for data struct");

	if (initialize_data(data, argv) == 1)
	{
		raise_error("Failed to initialize data struct");
		return (1);
	}

	printf("Nr philo: %d\n", data->nr_philo);
	return (0);
}