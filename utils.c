/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:32:38 by raanghel      #+#    #+#                 */
/*   Updated: 2023/08/14 17:02:16 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	raise_error(char *message)
{
	
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

int	check_digit(char *str)
{
	int	i;
	
	i = 0;
	
	while (str && str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
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


long int	current_time(void)
{
	struct	timeval		tv;
	long int			current_time;	

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}

void	own_usleep(t_philo *philo, long milliseconds)
{
	long int		start_time;
	(void) philo;

	start_time = current_time();
	while (current_time() - start_time < milliseconds)
		usleep(100);
}

void	output_message(t_philo *philo, t_activity activity)
{
	long int	curr_time;
	
	curr_time = current_time();
	pthread_mutex_lock(&philo->data->printing);
	if (activity == EAT)
		printf("(%ld) Philo %d is eating\n", curr_time, philo->pos);
	else if (activity == SLEEP)
		printf("(%ld) Philo %d is sleeping\n", curr_time, philo->pos);
	else if (activity == THINK)
		printf("(%ld) Philo %d is thinking\n", curr_time, philo->pos);
	else if (activity == FORK_R)
		printf("(%ld) Philo %d has taken a fork (%d)\n", curr_time,
			philo->pos, philo->right_fork + 1);
	else if (activity == FORK_L)
		printf("(%ld) Philo %d has taken a fork (%d)\n", curr_time,
			philo->pos, philo->left_fork + 1);
	else if (activity == RLS_FORK_L)
		printf("(%ld) Philo %d has released a fork (%d)\n", curr_time,
			philo->pos, philo->left_fork + 1);
	else if (activity == RLS_FORK_R)
		printf("(%ld) Philo %d has released a fork (%d)\n", curr_time,
			philo->pos, philo->right_fork + 1);
	else if (activity == DEAD)
		printf("(%ld) Philo %d died\n", curr_time, philo->pos);
	pthread_mutex_unlock(&philo->data->printing);
}

void	update_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->update_time);
	philo->time_last_meal = current_time();
	pthread_mutex_unlock(&philo->data->update_time);
}