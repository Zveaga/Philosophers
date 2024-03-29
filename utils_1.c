/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 19:13:08 by rares         #+#    #+#                 */
/*   Updated: 2024/02/07 19:13:16 by coxer         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	raise_error(t_data *data, char *message)
{
	free_data(data);
	printf("%s\n", message);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	number;

	i = 0;
	number = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
	{
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + str[i] - '0';
		if (number > 2147483647)
			return (-1);
		i++;
	}
	return (number);
}

void	update_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->update_time);
	philo->time_last_meal = current_time();
	pthread_mutex_unlock(&philo->data->update_time);
}

void	output_message(t_philo *philo, t_activity activity)
{
	long int	curr_time;

	pthread_mutex_lock(&philo->data->printing);
	curr_time = current_time() - philo->data->start_time;
	if (check_if_stop(philo->data) == false)
	{
		if (activity == EAT)
			printf(GRN"(%ld) Philo %d is eating\n"RESET, curr_time, philo->pos);
		else if (activity == SLEEP)
			printf(RED"(%ld) Philo %d is sleeping\n"RESET, curr_time, philo->pos);
		else if (activity == THINK)
			printf(MAGENTA"(%ld) Philo %d is thinking\n"RESET, curr_time, philo->pos);
		else if (activity == FORK_R)
			printf(BLUE"(%ld) Philo %d has taken a fork\n"RESET, curr_time,
				philo->pos);
		else if (activity == FORK_L)
			printf(BLUE"(%ld) Philo %d has taken a fork\n"RESET, curr_time,
				philo->pos);
	}
	pthread_mutex_unlock(&philo->data->printing);
}

// else if (activity == RLS_FORK_L)
// 	printf("(%ld) Philo %d has released a fork (%d)\n", curr_time,
// 		philo->pos, philo->left_fork + 1);
// else if (activity == RLS_FORK_R)
// 	printf("(%ld) Philo %d has released a fork (%d)\n", curr_time,
// 		philo->pos, philo->right_fork + 1);
