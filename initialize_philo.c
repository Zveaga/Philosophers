/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_philo.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:51:21 by raanghel      #+#    #+#                 */
/*   Updated: 2023/06/09 17:52:45 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"	

int	check_args(char **argv)
{
	if (check_digit(argv[1]) == 1
		|| check_digit(argv[2]) == 1
		|| check_digit(argv[3]) == 1
		|| check_digit(argv[4]) == 1)
	{
		return (1);
	}
	return (0);
}

int	check_positive_argv(char **argv)
{
	if (argv[1][0] == '-'
		|| argv[2][0] == '-'
		|| argv[3][0] == '-'
		|| argv[4][0] == '-')
	{
		return (1);
	}
	return (0);
}

// int	check_int(char **argv, t_data *data)
// {
// 	if (ft_strlen(argv[1]) > 11
// 		|| ft_strlen(argv[2]) > 11
// 		|| ft_strlen(argv[3]) > 11
// 		|| ft_strlen(argv[4]) > 11)
// 	{
// 		return(1);
// 	}
// 	if ((data->nr_philo < -2147483648 || data->nr_philo > 2147483647)
// 		|| (data->die_time < -2147483648 || data->die_time > 2147483647)
// 		|| (data->eat_time < -2147483648 || data->eat_time > 2147483647)
// 		|| (data->sleep_time < -2147483648 || data->sleep_time > 2147483647))
// 	{
// 		return(1);
// 	}
// 	return (0);
// }

int	check_int_overflow(char **argv)
{
	if (ft_atoi(argv[1]) == -1
		|| ft_atoi(argv[2]) == -1
		|| ft_atoi(argv[3]) == -1
		|| ft_atoi(argv[4]) == -1)
	{
		return (1);
	}
	return (0);
}

int	check_data(char **argv)
{
	if (check_args(argv) == 1)
	{
		printf("Program arguments should only contain digits\n");
		return(1);
	}
	if (check_positive_argv(argv) == 1)
	{
		printf("Program arguments should be positive\n");
		return(1);
	}
	if (check_int_overflow(argv) == 1)
	{
		printf("Program arg exceeds MAX_INT\n");
		return(1);
	}
	return (0);
}

int	initialize_data(t_data *data, char **argv)
{
	if (check_data(argv) == 1)
	{
		printf("Invalid arguments.\n");
		return (1);
	}
	data->nr_philo = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->start_time = 0;
	data->counter = 1;
	return (0);
}

static void	*routine(void *philos)
{
	//usleep(50);
	//printf("--DB--\n");
	t_data	*data;
	t_philo	*philo;
	int		i;
	
	//printf("1\n");
	philo = (t_philo *) philos;
	i = philo->pos;
	data = philo->data;
	pthread_mutex_lock(&philo->data->forks[0]);
	
	if (i != data->counter)
	{
		pthread_mutex_unlock(&philo->data->forks[0]);
		pthread_mutex_lock(&philo->data->forks[0]);
	}

	//printf("%d ", i);
	
	data->counter++;
	
	pthread_mutex_unlock(&philo->data->forks[0]);
	return (NULL);
}

// static void	*routine(void *philos)
// {
// 	t_philo	*philo;
// 	int		i;

// 	usleep(500);
// 	philo = (t_philo *) philos;
// 	i = philo->pos;
	
// 	pthread_mutex_lock(&philo->data->forks[0]);
	
// 	printf("%d ", i);
// 	pthread_mutex_unlock(&philo->data->forks[0]);
	
// 	return (NULL);
// }

int	initialize_philo(t_data *data)
{
	int			i;
	
	data->start_time = curret_time();
	//printf("\nStart time: %ld\n\n", data->start_time);
	if (data->start_time == -1)
		return (1);
	data->philos = malloc(data->nr_philo * sizeof(t_philo));
	if (data->philos == NULL)
		return (1);
	//printf("1\n");
	i = 0;
	while (i < data->nr_philo)
	{
		//printf("3\n");
		if (pthread_create(&data->philos[i].thread_id, NULL, &routine, &data->philos[i]) != 0)
			return (1);
		data->philos[i].pos = i + 1;
		data->philos[i].ms = 0;
		data->philos[i].data = data;
		data->philos[i].time_last_meal = 0;
		data->philos[i].left_fork = i;
		if (i == 0)
			data->philos[i].right_fork = data->nr_philo - 1;	
		data->philos[i].right_fork = i - 1;
		i++;
	}
	
	//printf("2\n");
	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			return (1);
		i++;  
	}
	return (0);	
}

int	initialize_forks(t_data *data)
{
	int	i;

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
	// if (pthread_mutex_init(&data->philo_created, NULL) != 0)
	// 		return (1);
	return (0);
}

int	destroy_mutex(t_data *data)
{
	int	i;

	
	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
