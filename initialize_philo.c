/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_philo.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:51:21 by raanghel      #+#    #+#                 */
/*   Updated: 2023/06/06 17:06:16 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"



int	initialize_data(t_data *data, char **argv)
{
	if (check_digit(argv[1]) == 1)
	{
		raise_error("Nr of philosophers should be a digit");
		return (0);
	}
	data->nr_philo = ft_atoi(argv[1]);
	return (0);
}

// void	create_philo(t_philo *philo)
// {
	
// }