/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:32:38 by raanghel      #+#    #+#                 */
/*   Updated: 2023/08/17 19:25:14 by raanghel      ########   odam.nl         */
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
	(void)philo;

	// if (philo->fully_ate == true)
	// 	return ;
	start_time = current_time();
	while ((current_time() - start_time) < milliseconds)
	{
		//if (philo->)
		usleep(200);
	}
}

// int32_t	delta_time(struct timeval t1, struct timeval t2)
// {
// 	struct timeval	delta;
// 	int32_t			timestamp;

// 	while ((t2.tv_usec < t1.tv_usec) && (t2.tv_sec > t1.tv_sec))
// 	{
// 		t2.tv_usec += 1000000;
// 		t2.tv_sec -= 1;
// 	}
// 	delta.tv_sec = t2.tv_sec - t1.tv_sec;
// 	delta.tv_usec = t2.tv_usec - t1.tv_usec;
// 	timestamp = delta.tv_sec * 1000000 + delta.tv_usec;
// 	return (timestamp / 1000);
// }

// void	own_usleep(t_philo *phil, long milli_secs)
// {
// 	struct timeval	start;
// 	struct timeval	current;
// 	//(void)phil;

// 	gettimeofday(&start, NULL);
// 	gettimeofday(&current, NULL);
// 	while (delta_time(start, current) < milli_secs)
// 	{
// 		if (phil->data->philo_alive == false)
// 			break ;
// 		usleep(50);
// 		gettimeofday(&current, NULL);
// 	}
// }

void	output_message(t_philo *philo, t_activity activity)
{
	long int	curr_time;
	
	curr_time = current_time();
	pthread_mutex_lock(&philo->data->printing);
	if ((philo->data->philo_alive == true) && (philo->fully_ate == false))
	{
		if (activity == EAT)
			printf(GREEN"(%ld) Philo %d is eating\n"RESET, curr_time, philo->pos);
		else if (activity == SLEEP)
			printf(RED"(%ld) Philo %d is sleeping\n"RESET, curr_time, philo->pos);
		else if (activity == THINK)
			printf(MAGENTA"(%ld) Philo %d is thinking\n"RESET, curr_time, philo->pos);
		else if (activity == FORK_R)
			printf(BLUE"(%ld) Philo %d has taken a fork (%d)\n"RESET, curr_time,
				philo->pos, philo->right_fork + 1);
		else if (activity == FORK_L)
			printf(BLUE"(%ld) Philo %d has taken a fork (%d)\n"RESET, curr_time,
				philo->pos, philo->left_fork + 1);
		else if (activity == RLS_FORK_L)
			printf("(%ld) Philo %d has released a fork (%d)\n", curr_time,
				philo->pos, philo->left_fork + 1);
		else if (activity == RLS_FORK_R)
			printf("(%ld) Philo %d has released a fork (%d)\n", curr_time,
				philo->pos, philo->right_fork + 1);
		else if (activity == DEAD)
			printf("(%ld) Philo %d died\n", curr_time, philo->pos);
	}
	pthread_mutex_unlock(&philo->data->printing);
}

void	update_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->update_time);
	//gettimeofday(&philo->time_last_meal, NULL);
	philo->time_last_meal = current_time();
	pthread_mutex_unlock(&philo->data->update_time);
}
